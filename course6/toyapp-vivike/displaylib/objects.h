#pragma once

#include <cstdint>
#include <array>

namespace Display {

struct Color
{
	uint8_t R;
	uint8_t G;
	uint8_t B;

	void redder(int amount);
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

struct Rectangle
{
	Vector3D corner1;
	Vector3D corner2;
	Vector3D corner3;
	Vector3D corner4;

	Rectangle move(Vector3D);
}

}