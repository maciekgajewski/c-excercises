#include "surface.h"
#include "objects.h"

#include <cassert>
#include <algorithm>

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

void Surface::DrawLine(Vector2D p1, Vector2D p2, Color color)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(p2.y - p1.y) > fabs(p2.x - p1.x));
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
	const float dy = fabs(p2.y - p1.y);

	float error = dx / 2.0f;
	const int ystep = (p1.y < p2.y) ? 1 : -1;
	int y = p1.y;

	const int maxX = p2.x;

	for(int x=p1.x; x<maxX; x++)
	{
		if(steep)
		{
			SetPixel({y,x}, color);
		}
		else
		{
			SetPixel({x,y}, color);
		}

		error -= dy;
		if(error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

}
