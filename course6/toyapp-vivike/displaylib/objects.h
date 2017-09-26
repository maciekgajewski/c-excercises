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
	
	Vector2D operator +(Vector2D b) { return { x + b.x, y + b.y}; }
	Vector2D operator +(int b) { return { x + b, y + b}; }	

	Vector2D operator *(int b) { return { x * b, y * b}; }

	Vector2D operator -(Vector2D r) { return { x - r.x, y - r.y}; }
	Vector2D operator -(int r) { return { x - r, y - r}; }

	Vector2D operator /(int r) { return { x / r, y / r}; }
};

struct Vector3D
{
	int x;
	int y;
	int z;

	Vector2D project2D();

	Vector3D operator +(Vector3D b) { return { x + b.x, y + b.y, z + b.z}; }
	Vector3D operator +(int b) { return { x + b, y + b, z + b}; }	

	Vector3D operator *(int b) { return { x * b, y * b, z * b}; }

	Vector3D operator -(Vector3D r) { return { x - r.x, y - r.y, z - r.z}; }
	Vector3D operator -(int r) { return { x - r, y - r, z - r}; }

	Vector3D operator /(int r) { return { x / r, y / r, z / r}; }
};

}