#pragma once

#include "sdlobject.h"

#include <SDL2/SDL.h>

#include <cstdint>

namespace Display {

class Surface : private SDLObject
{
public:
	Surface(int w, int h);
	~Surface();

	void Clear(std::uint8_t r, std::uint8_t g, std::uint8_t b);
	void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

private:

	friend class Window;

	SDL_Surface* mSurface;
};

}
