#pragma once

#include <cstdint>
#include <array>
#include <iostream>
#include <cmath>

#include "vector.h"

namespace Display {

struct Color
{
	uint8_t R;
	uint8_t G;
	uint8_t B;

	void redder(int amount);
};

struct Camera
{
	Pixel project2D(Vector3D original);
};

struct Rectangle
{
	Vector3D corner1;
	Vector3D corner2;
	Vector3D corner3;
	Vector3D corner4;

	Rectangle move(Vector3D);
};

}