#include "surface.h"
#include "objects.h"

#include <cassert>
#include <algorithm>

#include <iostream>

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
			Pixel pixel({x, y});
			SetPixel(pixel, backgroundColor);
		}
}

void Surface::SetPixel(Pixel pixel, Color currentColor)
{
	assert(mSurface);

	std::uint32_t pixelValue = (std::uint32_t(currentColor.R)<<16) + (std::uint32_t(currentColor.G)<<8) + currentColor.B;

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (pixel[1]*mSurface->pitch/4 + pixel[0]);
	*pixelAddr = pixelValue;
}

void Surface::DrawLine(Pixel p1, Pixel p2, Color color)
{
	// Bresenham's line algorithm
	int v1x = p1[0];
	int v1y = p1[1];
	int v2x = p2[0];
	int v2y = p2[1];

	bool steep = (std::fabs(v2y - v1y) > std::fabs(v2x - v1x));
	if(steep)
	{
		std::swap(v1x, v1y);
		std::swap(v2x, v2y);
	}

	if(v1x > v2x)
	{
		std::swap(v1x, v2x);
		std::swap(v1y, v2y);
	}

	const float dx = v2x - v1x;
	const float dy = std::fabs(v2y - v1y);

	float error = dx / 2.0f;
	const int ystep = (v1y < v2y) ? 1 : -1;
	int y = v1y;

	const int maxX = v2x;

	for(int x=v1x; x<=maxX; x++)
	{
		if(steep)
		{
			Pixel pixel({y,x});
			SetPixel(pixel, color);
		}
		else
		{
			Pixel pixel({x,y});
			SetPixel(pixel, color);
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
