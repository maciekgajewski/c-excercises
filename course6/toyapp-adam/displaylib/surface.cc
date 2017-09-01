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
	if (mSurface)
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
	auto offset = position.y * mSurface->pitch / 4 + position.x;
	auto* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + offset;
	*pixelAddr = (color.r << 16) + (color.g << 8) + color.b;
}

void Surface2D::DrawLine(Pixel start, Pixel end, Color color)
{
	// Bresenham's line algorithm
	const auto stepX = start.x < end.x ? 1 : -1;
	const auto stepY = start.y < end.y ? 1 : -1;

	if (start.x != end.x)
	{
		const float deltaX = end.x - start.x;
		const float deltaY = end.y - start.y;
		const auto deltaError = std::fabs(deltaY / deltaX);
		auto error = 0.0f;

		auto y = start.y;
		for (auto x = start.x;; x += stepX)
		{
			SetPixel({x, y}, color);
			if(x == end.x)
				break;

			error += deltaError;
			if (error > 0.5f)
			{
				y += stepY;
				error -= 1.0f;
			}
		}
	}
	else
	{
		for (auto y = start.y;; y += stepY)
		{
			SetPixel({start.x, y}, color);
			if(y == end.y)
				break;
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
