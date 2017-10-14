#include "surface_2d.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>

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
		{
			Pixel pixel{x, y};
			SetPixel(pixel, color);
			SetDepth(pixel, std::numeric_limits<float>::max());
		}
}

void Surface2D::SetDepth(Pixel position, float depth)
{
	mDepthBuffer[position[1] * mSurface->w + position[0]] = depth;
}

bool Surface2D::CheckSetDepth(Pixel position, float depth)
{
	if(position[0] >= 0 && position[0] < mSurface->w && position[1] >= 0 && position[1] < mSurface->h)
	{
		auto& currentDepth = mDepthBuffer[position[1] * mSurface->w + position[0]];
		if (currentDepth >= depth)
		{
			currentDepth = depth;
			return true;
		}
	}
	return false;
}

void Surface2D::SetPixel(Pixel position, Color color)
{
	if(position[0] >= 0 && position[0] < mSurface->w && position[1] >= 0 && position[1] < mSurface->h)
	{
		auto offset = position[1] * mSurface->pitch / 4 + position[0];
		auto* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + offset;
		*pixelAddr = (color.r << 16) + (color.g << 8) + color.b;
	}
}

// Bresenham's line algorithm
void Surface2D::DrawLine(Pixel p1, float p1Depth, Pixel p2, float p2Depth, Color color)
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

	auto delta = p2 - p1;
	delta[1] = std::fabs(delta[1]);
	auto error = delta[0] * 0.5f;
	auto length = delta.Length();

	auto y = p1[1];
	auto ystep = (p1[1] < p2[1]) ? 1 : -1;

	for(auto x = p1[0]; x < p2[0]; ++x)
	{
		Pixel pixel{x, y};
		Pixel p = pixel;

		if (steep)
			p = Pixel{y, x};

		auto distance = Pixel{p2 - pixel}.Length() / length;
		auto depth = p1Depth + distance * (p2Depth - p1Depth);

		if (CheckSetDepth(p, depth))
				SetPixel(p, color);

		error -= delta[1];
		if(error < 0)
		{
			y += ystep;
			error += delta[0];
		}
	}
}

// slow, naive algorithm. it has overdraw when triangles share edges!
void Surface2D::DrawTriangle(Pixel a, float aDepth, Pixel b, float bDepth, Pixel c, float cDepth, Color color)
{
	auto v0 = c - a;
	auto v1 = b - a;

	// cull back-facing triangles
	if (v1[0] * v0[1] - v1[1] * v0[0] > 0.0f)
		return;

	auto dot00 = v0.Dot(v0);
	auto dot01 = v0.Dot(v1);
	auto dot11 = v1.Dot(v1);
	auto invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);

	Pixel topLeft {
		std::min(a[0], std::min(b[0], c[0])),
		std::min(a[1], std::min(b[1], c[1]))
	};

	Pixel bottomRight {
		std::max(a[0], std::max(b[0], c[0])),
		std::max(a[1], std::max(b[1], c[1]))
	};

	for(auto y = topLeft[1]; y < bottomRight[1]; ++y)
		for(auto x = topLeft[0]; x < bottomRight[0]; ++x)
		{
			Pixel p{x, y};

			auto v2 = p - a;
			auto dot02 = v0.Dot(v2);
			auto dot12 = v1.Dot(v2);
			auto u = (dot11 * dot02 - dot01 * dot12) * invDenom;
			auto v = (dot00 * dot12 - dot01 * dot02) * invDenom;

			if ((u >= 0) && (v >= 0) && (u + v < 1.0f))
			{
				float depth = aDepth * u + bDepth * v + cDepth * (1.0f - u - v);
				if (CheckSetDepth(p, depth))
					SetPixel(p, color);
			}
		}
}

void Surface2D::SetPixel(Vector3D position, Color color)
{
	auto pixel = ToPixel(position);
	if (CheckSetDepth(pixel, position[2]))
		SetPixel(pixel, color);
}

void Surface2D::DrawLine(Vector3D start, Vector3D end, Color color)
{
	DrawLine(ToPixel(start), start[2], ToPixel(end), end[2], color);
}

void Surface2D::DrawTriangle(const Triangle3D& triangle, Color color)
{
	auto a = triangle[0];
	auto b = triangle[1];
	auto c = triangle[2];

	DrawTriangle(ToPixel(a), a[2], ToPixel(b), b[2], ToPixel(c), c[2], color);
}

Pixel Surface2D::ToPixel(Vector3D logicalCoordinates)
{
	return {
		static_cast<Pixel::Component>(mHalfDimensions[0] + logicalCoordinates[0] * mHalfDimensions[0]),
		static_cast<Pixel::Component>(mHalfDimensions[1] + logicalCoordinates[1] * mHalfDimensions[1])
	};
}

}
