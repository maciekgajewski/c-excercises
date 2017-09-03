#include "surface.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace Display {

Surface2D::Surface2D(int w, int h)
{
	mSurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	assert(mSurface);
}

Surface2D::~Surface2D()
{
	if(mSurface)
		SDL_FreeSurface(mSurface);
}

Pixel Surface2D::GetDimensions() const
{
	return {mSurface->w, mSurface->h};
}

void Surface2D::Clear(Color color)
{
	for(int y = 0; y < mSurface->h; ++y)
		for(int x = 0; x < mSurface->w; ++x)
			SetPixel({x, y}, color);
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
	const bool steep = (std::fabs(p2.y - p1.y) > std::fabs(p2.x - p1.x));
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

	const float dx = p2.x - p1.x;
	const float dy = std::fabs(p2.y - p1.y);
	float error = dx * 0.5f;

	int y = p1.y;
	const int ystep = (p1.y < p2.y) ? 1 : -1;

	if(steep)
	{
		for(int x = p1.x; x < p2.x; ++x)
		{
			SetPixel({y, x}, color);
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
		for(int x = p1.x; x < p2.x; ++x)
		{
			SetPixel({x, y}, color);
			error -= dy;
			if(error < 0)
			{
				y += ystep;
				error += dx;
			}
		}
	}
}

Surface3D::Surface3D(Surface2D& surface2D)
:	mSurface(surface2D)
{
	auto dimensions = surface2D.GetDimensions();
	mHalfDimensions.x = dimensions.x / 2;
	mHalfDimensions.y = dimensions.y / 2;
}

void Surface3D::Clear(Color color)
{
	mSurface.Clear(color);
}

void Surface3D::SetPixel(Vector3D vector, Color color)
{
	mSurface.SetPixel(GetPixel(vector), color);
}

void Surface3D::DrawLine(Vector3D start, Vector3D end, Color color)
{
	mSurface.DrawLine(GetPixel(start), GetPixel(end), color);
}

Pixel Surface3D::GetPixel(Vector3D point) const
{
	auto vector2D = Project(point);
	return {
		static_cast<Pixel::Coordinate>(mHalfDimensions.x + vector2D.x * mHalfDimensions.x),
		static_cast<Pixel::Coordinate>(mHalfDimensions.x + vector2D.y * mHalfDimensions.y),
	};
}

Vector2D Surface3D::Project(Vector3D vector) const
{
	return {
		vector.x / vector.z,
		vector.y / vector.z
	};
}

}
