#include "surface.h"

#include <cassert>

namespace Display {

Surface::Surface(Size size)
{
	mSurface = SDL_CreateRGBSurface(0, size.mWidth, size.mHeight, 32, 0, 0, 0, 0);
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
			SetPixel({x, y}, color);
}

void Surface::SetPixel(Vector2D point, Color color)
{
	assert(mSurface);

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (point.mY*mSurface->pitch/4 + point.mX);
	*pixelAddr = color.GetPixelValue();
}

}
