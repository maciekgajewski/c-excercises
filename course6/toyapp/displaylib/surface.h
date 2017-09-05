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

	void Clear(std::uint8_t r, std::uint8_t g, std::uint8_t b);
	void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	void DrawLine(Vector2D start, Vector2D end, RGB color);

private:

	friend class Window;

	SDL_Surface* mSurface;
};

class Surface3D
{
private:
	Surface* surface;
	Matrix cameraTransform;
	Vector2D Transform(Vector3D p)
	{
		Vector3D transformed = cameraTransform * p;
		return {transformed.x/transformed/z, transformed.y/transformed.z} // + plus sscaling and shift
	}
public:
	void SetPixel(Vector3D, RGB color) { surface->SetPixel(Transform(p), color);
	void DrawLine(Vector3D start, Vector3D end, RGB color)
	{
		surface->DrawLine(Transform(start), Transfom(end), color);
	}
}

class Cube
{
	Transform tr;
	RGB color;

	void Draw(Surface3D& surf)
	{
		tr.DrawLine(tr*Vector3D{-1, -1, -1}, tr*{-1, -1, +1}, color);
		// etc
	}

}


}
