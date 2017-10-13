#include "surface_2d.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace Display {

Surface2D::Surface2D(Pixel dimensions)
:	mHalfDimensions{dimensions * 0.5f}
{
	mDepthBuffer = std::make_unique<float[]>(dimensions[0] * dimensions[1]);
	mSurface = SDL_CreateRGBSurface(0, dimensions[0], dimensions[1], 32, 0, 0, 0, 0);
	assert(mSurface);
}

Surface2D::~Surface2D()
{
	SDL_FreeSurface(mSurface);
}

void Surface2D::Clear(Color color)
{
	for(int y = 0; y < mSurface->h; ++y)
		for(int x = 0; x < mSurface->w; ++x)
			SetPixel(Pixel{x, y}, color);
}

void Surface2D::SetPixel(Pixel position, Color color)
{
	if(position[0] > 0 && position[0] < mSurface->w && position[1] > 0 && position[1] < mSurface->h)
	{
		auto offset = position[1] * mSurface->pitch / 4 + position[0];
		auto* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + offset;
		*pixelAddr = (color.r << 16) + (color.g << 8) + color.b;
	}
}

// Bresenham's line algorithm
void Surface2D::DrawLine(Pixel p1, Pixel p2, Color color)
{
	// @todo clamp p1 and p2 to borders, and don't start drawing if it's completely outside
	//       then perhaps remove the check from within SetPixel
	bool steep = (std::abs(p2[1] - p1[1]) > std::abs(p2[0] - p1[0]));
	if(steep)
	{
		std::swap(p1[0], p1[1]);
		std::swap(p2[0], p2[1]);
	}

	if(p1[0] > p2[0])
	{
		std::swap(p1[0], p2[0]);
		std::swap(p1[1], p2[1]);
	}

	auto dx = p2[0] - p1[0];
	auto dy = std::fabs(p2[1] - p1[1]);
	auto error = dx * 0.5f;

	auto y = p1[1];
	auto ystep = (p1[1] < p2[1]) ? 1 : -1;

	if(steep)
	{
		for(auto x = p1[0]; x < p2[0]; ++x)
		{
			SetPixel(Pixel{y, x}, color);
			error -= dy;
			if(error < 0)
			{
				y += ystep;
				error += dx;
			}
		}
	}
	else
	{
		for(auto x = p1[0]; x < p2[0]; ++x)
		{
			SetPixel(Pixel{x, y}, color);
			error -= dy;
			if(error < 0)
			{
				y += ystep;
				error += dx;
			}
		}
	}
}

// slow, naive algorithm. it has overdraw when triangles share edges!
void Surface2D::DrawTriangle(Pixel a, Pixel b, Pixel c, Color color)
{
	Pixel topLeft {
		std::min(a[0], std::min(b[0], c[0])),
		std::min(a[1], std::min(b[1], c[1]))
	};

	Pixel bottomRight {
		std::max(a[0], std::max(b[0], c[0])),
		std::max(a[1], std::max(b[1], c[1]))
	};

	auto edge1 = b - a;
	auto edge2 = c - a;

	// flip winding if necessary
	if (edge1[0] * edge2[1] - edge1[1] * edge2[0] > 0.0f)
	{
		auto temp = a;
		a = b;
		b = temp;
	}

	for(auto y = topLeft[1]; y < bottomRight[1]; ++y)
		for(auto x = topLeft[0]; x < bottomRight[0]; ++x)
			if((a[0] - b[0]) * (y - a[1]) - (a[1] - b[1]) * (x - a[0]) >= 0 &&
			   (b[0] - c[0]) * (y - b[1]) - (b[1] - c[1]) * (x - b[0]) >= 0 &&
			   (c[0] - a[0]) * (y - c[1]) - (c[1] - a[1]) * (x - c[0]) >= 0)
			{
				SetPixel(Pixel{x, y}, color);
			}
}

void Surface2D::SetPixel(Vector2D position, Color color)
{
	SetPixel(ToPixel(position), color);
}

void Surface2D::DrawLine(Vector2D start, Vector2D end, Color color)
{
	DrawLine(ToPixel(start), ToPixel(end), color);
}

void Surface2D::DrawTriangle(const Triangle2D& triangle, Color color)
{
	DrawTriangle(ToPixel(triangle[0]), ToPixel(triangle[1]), ToPixel(triangle[2]), color);
}

void Surface2D::DrawTriangles(const std::vector<Triangle2D>& triangles, Color color)
{
	for(auto& triangle : triangles)
		DrawTriangle(triangle, color);
}

Pixel Surface2D::ToPixel(Vector2D logicalCoordinates)
{
	return {
		static_cast<Pixel::Component>(mHalfDimensions[0] + logicalCoordinates[0] * mHalfDimensions[0]),
		static_cast<Pixel::Component>(mHalfDimensions[1] + logicalCoordinates[1] * mHalfDimensions[1])
	};
}

}
