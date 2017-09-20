#include "surface_2d.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace Display {

Surface2D::Surface2D(Pixel dimensions)
:	mHalfDimensions{dimensions.x / 2, dimensions.y / 2}
{
	mSurface = SDL_CreateRGBSurface(0, dimensions.x, dimensions.y, 32, 0, 0, 0, 0);
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
	if(position.x > 0 && position.x < mSurface->w && position.y > 0 && position.y < mSurface->h)
	{
		auto offset = position.y * mSurface->pitch / 4 + position.x;
		auto* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + offset;
		*pixelAddr = (color.r << 16) + (color.g << 8) + color.b;
	}
}

// Bresenham's line algorithm
void Surface2D::DrawLine(Pixel p1, Pixel p2, Color color)
{
	// @todo clamp p1 and p2 to borders, and don't start drawing if it's completely outside
	//       then perhaps remove the check from within SetPixel
	bool steep = (std::abs(p2.y - p1.y) > std::abs(p2.x - p1.x));
	if(steep)
	{
		std::swap(p1.x, p1.y);
		std::swap(p2.x, p2.y);
	}

	if(p1.x > p2.x)
	{
		std::swap(p1.x, p2.x);
		std::swap(p1.y, p2.y);
	}

	auto dx = p2.x - p1.x;
	auto dy = std::fabs(p2.y - p1.y);
	auto error = dx * 0.5f;

	auto y = p1.y;
	auto ystep = (p1.y < p2.y) ? 1 : -1;

	if(steep)
	{
		for(auto x = p1.x; x < p2.x; ++x)
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
		for(auto x = p1.x; x < p2.x; ++x)
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
		std::min(a.x, std::min(b.x, c.x)),
		std::min(a.y, std::min(b.y, c.y))
	};

	Pixel bottomRight {
		std::max(a.x, std::max(b.x, c.x)),
		std::max(a.y, std::max(b.y, c.y))
	};

	for(auto y = topLeft.y; y < bottomRight.y; ++y)
		for(auto x = topLeft.x; x < bottomRight.x; ++x)
			if((a.x - b.x) * (y - a.y) - (a.y - b.y) * (x - a.x) >= 0 &&
			   (b.x - c.x) * (y - b.y) - (b.y - c.y) * (x - b.x) >= 0 &&
			   (c.x - a.x) * (y - c.y) - (c.y - a.y) * (x - c.x) >= 0)
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

Pixel Surface2D::ToPixel(Vector2D logicalCoordinates)
{
	return {
		static_cast<Pixel::Coordinate>(mHalfDimensions.x + logicalCoordinates.x * mHalfDimensions.x),
		static_cast<Pixel::Coordinate>(mHalfDimensions.y + logicalCoordinates.y * mHalfDimensions.y)
	};
}

}
