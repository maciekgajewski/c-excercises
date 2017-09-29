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
	void SetPixel(Vector<int, 2>& pixel, Color currentColor);
	void DrawLine(Vector<int, 2>& p1, Vector<int, 2>& p2, Color color);

private:

	friend class Window;

	SDL_Surface* mSurface;
};

}
