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
	void DrawLine(Vector2D v1, Vector2D v2, Color color);
	void DrawRect(Rect rect, Color color);
	void DrawRect(Rect rect, Degree rotationAngle, Color color);

	void DrawPolygon(const Polygon& p, Color color);
	void DrawPolygon(const Polygon& p, Color color, Color cornerColor);

	void DrawCube(const Polyhedron& p, Color color);

private:

	friend class Window;

	SDL_Surface* mSurface;
};

}
