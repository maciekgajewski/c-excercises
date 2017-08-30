#pragma once

#include "sdlobject.h"
#include "color.h"
#include "point2d.h"
#include "point3d.h"

#include <SDL2/SDL.h>

#include <cstdint>

namespace Display {

class Surface : private SDLObject
{
public:
	Surface(int w, int h);
	~Surface();

	void Clear(Color color);
	void SetPixel(Point2D point, Color color);
	void DrawCube(Point3D point, int size);

private:

	friend class Window;

	SDL_Surface* mSurface;
};

}
