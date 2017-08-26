#pragma once

#include "sdlobject.h"
#include "types.h"

#include <SDL2/SDL.h>

#include <cstdint>

namespace Display {

class Surface : private SDLObject
{
public:
	Surface(Size size);
	~Surface();

	void Clear(Color color);
	void SetPixel(Vector2D point, Color color);

private:

	friend class Window;

	SDL_Surface* mSurface;
};

}
