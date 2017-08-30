#include "surface.h"
#include "color.h"
#include "point2d.h"
#include "point3d.h"

#include <cassert>

namespace Display {

Surface::Surface(int w, int h)
{
	mSurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
}

Surface::~Surface()
{
	if (mSurface)
		SDL_FreeSurface(mSurface);
}

void Surface::Clear(Color color)
{
	assert(mSurface);

	for(int y = 0; y < mSurface->h; y++)
		for(int x = 0; x < mSurface->w; x++)
		{
			Point2D point(x, y);
			SetPixel(point, color);
		}
}

void Surface::SetPixel(Point2D point, Color color)
{
	assert(mSurface);

	std::uint32_t pixelValue = (std::uint32_t(color.r)<<16) + (std::uint32_t(color.g)<<8) + color.b;

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (point.y*mSurface->pitch/4 + point.x);
	*pixelAddr = pixelValue;
}

void Surface::DrawCube(Point3D point, int size)
{

}

}
