#pragma once

#include "cube.h"
#include "pixel.h"
#include "rgb.h"
#include "sdlobject.h"

#include <SDL2/SDL.h>

namespace Display {

class Surface : private SDLObject
{
public:
	Surface(int w, int h);
	~Surface();

	void Clear(Rgb color);
	void SetPixel(Pixel position, Rgb color);
	void DrawVertex(Vector3D vertex, Rgb color);
	void DrawCube(Cube& cube, Rgb color);
private:

	friend class Window;

	SDL_Surface* mSurface;
};

}
