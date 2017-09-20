#include "surface.h"

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

void Surface::Clear(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	assert(mSurface);

	for(int y = 0; y < mSurface->h; y++)
		for(int x = 0; x < mSurface->w; x++)
			SetPixel(x, y, r, g, b);
}

void Surface::SetPixel(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	assert(mSurface);

	std::uint32_t pixelValue = (std::uint32_t(r)<<16) + (std::uint32_t(g)<<8) + b;

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (y*mSurface->pitch/4 + x);
	*pixelAddr = pixelValue;
}

}
