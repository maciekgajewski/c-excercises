#pragma once

#include "sdlobject.h"
#include "color.h"
#include "vector2d.h"
#include "vector3d.h"

#include <SDL2/SDL.h>

#include <cstdint>

namespace Display {

class Surface : private SDLObject
{
public:
	Surface(int w, int h);
	~Surface();

	void Clear(Color color);
	void SetPixel(Vector2D point, Color color);
	Vector2D getProjection(Vector3D vector);

private:

	friend class Window;

	SDL_Surface* mSurface;
};

}
