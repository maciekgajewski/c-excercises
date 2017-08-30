#include "surface.h"

#include "functions.h"

#include <cassert>
#include <algorithm>
#include <stdexcept>

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

void Surface::SetPixel(Pixel p, Color color)
{
	assert(mSurface);

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (p.mY*mSurface->pitch/4 + p.mX);
	*pixelAddr = color.GetPixelValue();
}

void Surface::DrawLine(Pixel p1, Pixel p2, Color color)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(p2.mY - p1.mY) > fabs(p2.mX - p1.mX));
	if(steep)
	{
		std::swap(p1.mX, p1.mY);
		std::swap(p2.mX, p2.mY);
	}

	if(p1.mX > p2.mX)
	{
		std::swap(p1.mX, p2.mX);
		std::swap(p1.mY, p2.mY);
	}

	const float dx = p2.mX - p1.mX;
	const float dy = fabs(p2.mY - p1.mY);

	float error = dx / 2.0f;
	const int ystep = (p1.mY < p2.mY) ? 1 : -1;
	int y = p1.mY;

	const int maxX = p2.mX;

	for(int x=p1.mX; x<maxX; x++)
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

Size Surface::GetSize() const
{
	return {mSurface->w, mSurface->h};
}

}
