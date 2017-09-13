#pragma once

#include "sdlobject.h"

#include <SDL2/SDL.h>

#include <cstdint>

namespace Display {

	class Vector2D
	{
	public:
		double x, y;
	};

	class Matrix
	{};

	class RGB
	{
	public:
		uint8_t r, g, b;
	};

	class Vector3D
	{
	public:
		double x, y, z;
	};

	Vector3D operator * (Matrix m, Vector3D v)
	{
		return v;
	}

class Surface : private SDLObject
{
public:
	Surface(int w, int h);
	~Surface();

	void Clear(std::uint8_t r, std::uint8_t g, std::uint8_t b);

	void SetPixel(Vector2D p, RGB color) { SetPixel(p.x, p.y, color.r, color.g, color.b); }

	void SetPixel(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b);

	
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
		return { transformed.x / transformed.z, transformed.y / transformed.z };// + plus sscaling and shift
	}
public:
	void SetPixel(Vector3D p, RGB color)
	{
		surface->SetPixel(Transform(p), color);
	}

	void DrawLine(Vector3D start, Vector3D end, RGB color)
	{
		surface->DrawLine(Transform(start), Transform(end), color);
	}
};

class Cube
{
	Matrix transformation;
	RGB color;

	void Draw(Surface3D& surface)
	{
		surface.DrawLine(transformation * Vector3D{-1, -1, -1}, transformation * Vector3D{-1, -1, +1}, color);
		// etc
	}
};


};