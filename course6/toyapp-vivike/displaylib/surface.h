#pragma once

#include "sdlobject.h"
#include "objects.h"

#include <SDL2/SDL.h>

#include <cstdint>

namespace Display {

class Surface : private SDLObject
{
public:
	Surface(int w, int h);
	~Surface();

	void Clear(Color backgroundColor);
	void SetPixel(Vector2D pixel, Color currentColor);

private:

	friend class Window;

	SDL_Surface* mSurface;
};

}
