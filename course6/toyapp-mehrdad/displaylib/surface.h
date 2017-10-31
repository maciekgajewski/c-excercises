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

	//Basic drawing functions
	void SetPixel(Pixel p, Color color);
	void DrawLine(Pixel p1, Pixel p2, Color color);

	Size GetSize() const;

private:
	uint32_t GetPixelValue(Color c) const;

private:

	friend class Window;

	SDL_Surface* mSurface;
};

}
