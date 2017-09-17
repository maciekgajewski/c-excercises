#pragma once

#include "sdlobject.h"
#include "color.h"
#include "vector2d.h"
#include "vector3d.h"

#include <SDL2/SDL.h>

namespace Display {

class Surface : private SDLObject
{

public:
	Surface(int w, int h);
	~Surface();

	void Clear(Color color);
	void SetPixel(const Vector2D& point, Color color);

private:

	friend class Window;
	friend class Surface3D;

	SDL_Surface* mSurface;
};

}
