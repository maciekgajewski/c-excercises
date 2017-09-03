#pragma once

#include "pixel.h"
#include "color.h"
#include "math/vector.h"
#include "sdlobject.h"
#include <SDL2/SDL.h>

namespace Display {

using Math::Vector2D;
using Math::Vector3D;

class Surface2D : private SDLObject
{
	friend class Window;
public:
	Surface2D(int w, int h);
	~Surface2D();

	Pixel GetDimensions() const;

	void Clear(Color color);
	void SetPixel(Pixel position, Color color);
	void DrawLine(Pixel start, Pixel end, Color color);
private:
	SDL_Surface* mSurface;
};


class Surface3D
{
public:
	Surface3D(Surface2D& surface2D);

	void Clear(Color color);
	void SetPixel(Vector3D vector, Color color);
	void DrawLine(Vector3D start, Vector3D end, Color color);
private:
	Surface2D& mSurface;
	Pixel mHalfDimensions;

	Pixel GetPixel(Vector3D point) const;
	Vector2D Project(Vector3D vector) const;
};

}
