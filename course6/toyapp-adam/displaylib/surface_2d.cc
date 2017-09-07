#include "surface_2d.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace Display {

Surface2D::Surface2D(int w, int h)
:	mHalfDimensions{w / 2, h / 2}
{
	mSurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
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

void Surface2D::DrawLine(Pixel p1, Pixel p2, Color color)
{
	// Bresenham's line algorithm
	// @todo clamp p1 and p2 to borders, and don't start drawing if it's completely outside
	//       then perhaps remove the check from within SetPixel
	bool steep = (std::fabs(p2.y - p1.y) > std::fabs(p2.x - p1.x));
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

void Surface2D::SetPixel(Vector2D position, Color color)
{
	SetPixel(GetPhysicalCoordinates(position), color);
}

void Surface2D::DrawLine(Vector2D start, Vector2D end, Color color)
{
	DrawLine(GetPhysicalCoordinates(start), GetPhysicalCoordinates(end), color);
}

Pixel Surface2D::GetPhysicalCoordinates(Vector2D logicalCoordinates)
{
	return {
		static_cast<Pixel::Coordinate>(mHalfDimensions.x + logicalCoordinates.x * mHalfDimensions.x),
		static_cast<Pixel::Coordinate>(mHalfDimensions.y + logicalCoordinates.y * mHalfDimensions.y)
	};
}

}
