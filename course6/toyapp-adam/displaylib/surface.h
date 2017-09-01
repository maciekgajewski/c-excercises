#pragma once

#include "pixel.h"
#include "color.h"
#include "sdlobject.h"
#include "vector.h"
#include <SDL2/SDL.h>

namespace Display {

class Surface2D : private SDLObject
{
	friend class Window;
public:
	Surface2D(int w, int h);
	~Surface2D();

	Pixel GetDimensions() const;

	void Clear(Color color);
	void SetPixel(Pixel position, Color color);
private:
	SDL_Surface* mSurface;
};


class Surface3D
{
public:
	Surface3D(Surface2D& surface2D);
	
	void SetPixel(Vector3D vector, Color color);
private:
	Surface2D& mSurface;
	Pixel mHalfDimensions;

	Pixel GetPixel(Vector2D point) const;
	Vector2D Project(Vector3D vector) const;
};

}
