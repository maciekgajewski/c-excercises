#pragma once

#include <cstdint>

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
	
	//Vector2D operator +(Vector2D b) { return { x + b.x, y + b.y}; }
	
};

//Vector2D operator +(Vector2D a, int b) { return { a.x + b, a.y + b}; }
Vector2D operator +(int b, Vector2D a) { return { a.x + b, a.y + b}; }

struct Vector3D
{
	int x;
	int y;
	int z;

	Vector2D project2D();
};

}