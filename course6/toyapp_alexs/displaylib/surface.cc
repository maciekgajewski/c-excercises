#include "surface.h"
#include "color.h"
#include "vector2d.h"
#include "vector3d.h"

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

void Surface::Clear(Color color)
{
	assert(mSurface);

	for(int y = 0; y < mSurface->h; y++)
		for(int x = 0; x < mSurface->w; x++)
		{
			SetPixel({x, y}, color);
		}
}

void Surface::SetPixel(Vector2D point, Color color)
{
	assert(mSurface);

	std::uint32_t pixelValue = (std::uint32_t(color.r)<<16) + (std::uint32_t(color.g)<<8) + color.b;

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (point.y*mSurface->pitch/4 + point.x);
	*pixelAddr = pixelValue;
}

Vector2D Surface::getProjection(Vector3D vector)
{
	const float scale = 3;
	
	int scaleX = mSurface->w / scale;
	int scaleY = mSurface->h / scale;
	int centerX = mSurface->w / 2;
	int centerY = mSurface->h / 2;

	return Vector2D {
		centerX + static_cast<int>(vector.x / vector.z * scaleX),
		centerY - static_cast<int>(vector.y / vector.z * scaleY)
	};;
}

}
