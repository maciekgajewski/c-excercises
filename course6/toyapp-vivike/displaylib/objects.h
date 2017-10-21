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

class Square
{
	std::array<Vector3D, 4> base_square;
	float len;
	Vector3D loc_center;
	Vector3D orient;

	Vector3D transformCorner(Vector3D corner);

public:
	Square(float edge_length, Vector3D center_location, Vector3D orientation);

	void move(Vector3D);
	std::array<std::array<Vector3D, 2>, 4> edges();
};



}