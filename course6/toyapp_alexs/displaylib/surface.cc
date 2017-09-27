#include "surface.h"
#include "color.h"
#include "vector2d.h"
#include "vector3d.h"

#include <cmath>
#include <algorithm>
#include <cassert>

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

void Surface::Clear(Color color)
{
	assert(mSurface);

	for(int y = 0; y < mSurface->h; y++)
		for(int x = 0; x < mSurface->w; x++)
		{
			SetPixel({x, y}, color);
		}
}

void Surface::SetPixel(const Vector2D& point, Color color)
{
	assert(mSurface);

	std::uint32_t pixelValue = (std::uint32_t(color.r)<<16) + (std::uint32_t(color.g)<<8) + color.b;

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (point.y*mSurface->pitch/4 + point.x);
	*pixelAddr = pixelValue;
}

void Surface::DrawLine(const Vector2D& a, const Vector2D& b, Color color)
{
	if (std::abs(a.y - b.y) < std::abs(a.x - b.x) || a.y == b.y)
	{
		double k = (double)(a.y - b.y) / (double)(a.x - b.x);
		double m = k * a.x - a.y;

		int min = std::min(a.x, b.x);
		int max = std::max(a.x, b.x);

		for (int x = min; x <= max; x++)
		{
			SetPixel({ x, (int)(k * x - m)}, color);
		}
	}
	else
	{
		double k =  (double)(a.x - b.x) / (double)(a.y - b.y);
		double m = k * a.y - a.x;

		int min = std::min(a.y, b.y);
		int max = std::max(a.y, b.y);

		for (int y = min; y <= max; y++)
		{
			SetPixel({ (int)(k * y - m) , y}, color);
		}
	}
}

}
