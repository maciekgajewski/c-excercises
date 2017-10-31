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

class Triangle
{
	std::array<Vector3D, 3> corners;

public:
	Triangle(Vector3D point1, Vector3D point2, Vector3D point3)
	{
		corners[0] = point1;
		corners[1] = point2;
		corners[2] = point3;
	}

	Vector3D& operator [](int elem) 
	{ 
		return this->corners[elem];
	}

	Vector3D operator [](int elem) const
	{ 
		return this->corners[elem];
	}

	void move(Vector3D);
	std::array<std::array<Vector3D, 2>, 3> edges();
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