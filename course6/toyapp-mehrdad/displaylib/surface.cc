#include "surface.h"

#include <cassert>
#include <algorithm>

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

void Surface::DrawLine(Vector2D v1, Vector2D v2, Color color)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(v2.mY - v1.mY) > fabs(v2.mX - v1.mX));
	if(steep)
	{
		std::swap(v1.mX, v1.mY);
		std::swap(v2.mX, v2.mY);
	}

	if(v1.mX > v2.mX)
	{
		std::swap(v1.mX, v2.mX);
		std::swap(v1.mY, v2.mY);
	}

	const float dx = v2.mX - v1.mX;
	const float dy = fabs(v2.mY - v1.mY);

	float error = dx / 2.0f;
	const int ystep = (v1.mY < v2.mY) ? 1 : -1;
	int y = v1.mY;

	const int maxX = v2.mX;

	for(int x=v1.mX; x<maxX; x++)
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
