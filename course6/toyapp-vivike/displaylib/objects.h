#pragma once

#include <cstdint>

namespace Display {

struct Color
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

struct Vector2D
{
	int x;
	int y;

	void move(int xmove, int ymove);
};

struct Vector3D
{
	int x;
	int y;
	int z;

	Vector2D project2D();
};

}