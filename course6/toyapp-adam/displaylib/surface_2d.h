#pragma once

#include "color.h"
#include "math/vector.h"
#include "sdlobject.h"
#include "util/pixel.h"
#include <SDL2/SDL.h>

namespace Display {

using Math::Vector2D;
using Util::Pixel;

class Surface2D : private SDLObject
{
	friend class Window;
public:
	Surface2D(Pixel dimensions);
	~Surface2D();

	Pixel GetDimensions() const { return {mSurface->w, mSurface->h}; }

	void Clear(Color color);
	void SetPixel(Pixel position, Color color);
	void DrawLine(Pixel start, Pixel end, Color color);
	void SetPixel(Vector2D position, Color color);
	void DrawLine(Vector2D start, Vector2D end, Color color);
private:
	SDL_Surface* mSurface;
	Pixel mHalfDimensions;

	Pixel GetPhysicalCoordinates(Vector2D logicalCoordinates);
};

}
