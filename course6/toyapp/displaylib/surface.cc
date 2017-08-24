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

void Surface::Clear(Rgb color)
{
	assert(mSurface);

	for(int y = 0; y < mSurface->h; y++)
		for(int x = 0; x < mSurface->w; x++)
			SetPixel(Pixel{x, y}, color);
}

void Surface::SetPixel(Pixel position, Rgb color)
{
	assert(mSurface);

	std::uint32_t pixelValue = (std::uint32_t(color.r)<<16) + (std::uint32_t(color.g)<<8) + color.b;

	auto offset = position.y*mSurface->pitch/4 + position.x;
	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + offset;
	*pixelAddr = pixelValue;
}

void Surface::DrawVertex(Vector3D vertex, Rgb color)
{
	auto point2D = vertex.project();
	Pixel halfScreen{mSurface->w / 2, mSurface->h / 2};
	Pixel pixel {
		static_cast<int>(halfScreen.x + point2D.x * halfScreen.x),
		static_cast<int>(halfScreen.x + point2D.y * halfScreen.y),
	};

	SetPixel(pixel, color);
}

void Surface::DrawCube(Cube& cube, Rgb color)
{
	for(unsigned i = 0; i < Cube::VERTEX_COUNT; ++i)
		DrawVertex(cube.vertices[i], color);
}

}
