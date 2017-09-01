#include "surface.h"

#include <cassert>

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
	return {
		static_cast<Pixel::Coordinate>(mSurface->w),
		static_cast<Pixel::Coordinate>(mSurface->h)
	};
}

void Surface2D::Clear(Color color)
{
	unsigned w = mSurface->w;
	unsigned h = mSurface->h;

	for(unsigned y = 0; y < h; ++y)
		for(unsigned x = 0; x < w; ++x)
			SetPixel({x, y}, color);
}

void Surface2D::SetPixel(Pixel position, Color color)
{
	auto offset = position.y * mSurface->pitch / 4 + position.x;
	auto* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + offset;
	*pixelAddr = (color.r << 16) + (color.g << 8) + color.b;
}


Surface3D::Surface3D(Surface2D& surface2D)
:	mSurface(surface2D)
{
	auto dimensions = surface2D.GetDimensions();
	mHalfDimensions.x = dimensions.x / 2u;
	mHalfDimensions.y = dimensions.y / 2u;
}

void Surface3D::SetPixel(Vector3D vector, Color color)
{
	auto vector2D = Project(vector);
	auto pixel = GetPixel(vector2D);
	mSurface.SetPixel(pixel, color);
}

Pixel Surface3D::GetPixel(Vector2D point) const
{
	return {
		static_cast<Pixel::Coordinate>(mHalfDimensions.x + point.x * mHalfDimensions.x),
		static_cast<Pixel::Coordinate>(mHalfDimensions.x + point.y * mHalfDimensions.y),
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
