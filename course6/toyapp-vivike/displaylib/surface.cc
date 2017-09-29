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
			Vector<int, 2> pixel{x, y};
			SetPixel(pixel, backgroundColor);
		}
}

void Surface::SetPixel(Vector<int, 2>& pixel, Color currentColor)
{
	assert(mSurface);

	std::uint32_t pixelValue = (std::uint32_t(currentColor.R)<<16) + (std::uint32_t(currentColor.G)<<8) + currentColor.B;

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (pixel.vec[1]*mSurface->pitch/4 + pixel.vec[0]);
	*pixelAddr = pixelValue;
}

void Surface::DrawLine(Vector<int, 2>& p1, Vector<int, 2>& p2, Color color)
{
	// Bresenham's line algorithm
	Vector<int, 2> steepTest = p2 - p1;
	std::cout << std::endl;
	p1.print();
	p2.print();
	steepTest.print();
	bool steep = (std::fabs(steepTest.vec[1]) > std::fabs(steepTest.vec[0]));
	if(steep)
	{
		std::swap(p1.vec[0], p1.vec[1]);
		std::swap(p2.vec[0], p2.vec[1]);
	}

	if(p1.vec[0] > p2.vec[0])
	{
		std::swap(p1.vec[0], p2.vec[0]);
		std::swap(p1.vec[1], p2.vec[1]);
	}

	const float dx = p2.vec[0] - p1.vec[0];
	const float dy = std::fabs(p2.vec[1] - p1.vec[1]);

	float error = dx / 2.0f;
	const int ystep = (p1.vec[1] < p2.vec[1]) ? 1 : -1;
	int y = p1.vec[1];

	const int maxX = p2.vec[0];

	for(int x=p1.vec[0]; x<maxX; x++)
	{
		if(steep)
		{
			Vector<int, 2> pixel{y,x};
			SetPixel(pixel, color);
			std::cout << "steep pixel " << std::endl;
			pixel.print();
		
		}
		else
		{
			Vector<int, 2> pixel{x,y};
			SetPixel(pixel, color);
			std::cout << "non steep pixel " << std::endl;
			pixel.print();
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
