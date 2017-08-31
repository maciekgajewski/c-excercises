#include "surface.h"
#include "objects.h"

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

void Surface::Clear(Color backgroundColor)
{
	assert(mSurface);

	for(int y = 0; y < mSurface->h; y++)
		for(int x = 0; x < mSurface->w; x++)
		{
			Vector2D pixel;
			pixel.x = x;
			pixel.y = y;
			SetPixel(pixel, backgroundColor);
		}
}

void Surface::SetPixel(Vector2D pixel, Color currentColor)
{
	assert(mSurface);

	std::uint32_t pixelValue = (std::uint32_t(currentColor.R)<<16) + (std::uint32_t(currentColor.G)<<8) + currentColor.B;

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (pixel.y*mSurface->pitch/4 + pixel.x);
	*pixelAddr = pixelValue;
}

}
