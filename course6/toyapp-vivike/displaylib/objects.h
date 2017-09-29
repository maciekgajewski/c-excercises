#pragma once

#include <cstdint>
#include <array>
#include <iostream>

namespace Display {

struct Color
{
	uint8_t R;
	uint8_t G;
	uint8_t B;

	void redder(int amount);
};


template<typename T, int length>
struct Vector
{
	int vec[length];

	Vector<T, length> operator +(Vector& b) 
	{ 
		Vector<T, length> newVec;
		for(int i=0; i<length; i++)
		{
			newVec.vec[i] = this->vec[i] + b.vec[i];
		}
		return newVec;
	}

	Vector<T, length> operator *(int b) 
	{ 
		Vector<T, length> newVec;
		for(int i=0; i<length; i++)
		{
			newVec.vec[i] = this->vec[i] * b;
		}
		return newVec;
	}

	Vector<T, length> operator -(Vector& r) 
	{ 
		Vector<T, length> newVec;
		for(int i=0; i<length; i++)
		{
			newVec.vec[i] = this->vec[i] - r.vec[i];
		}
		return newVec;
	}

	Vector<T, length> operator /(int r) 
	{ 
		Vector<T, length> newVec;
		for(int i=0; i<length; i++)
		{
			newVec.vec[i] = this->vec[i] / r;
		}
		return newVec;
	}	

	void print()
	{
		std::string mystr;
		for(T v : vec)
		{
			std::cout << v << std::endl;
		}
		

	}
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

	Vector3D operator +(Vector3D b) { return { x + b.x, y + b.y, z + b.z}; }
	Vector3D operator +(int b) { return { x + b, y + b, z + b}; }	

	Vector3D operator *(int b) { return { x * b, y * b, z * b}; }

	Vector3D operator -(Vector3D r) { return { x - r.x, y - r.y, z - r.z}; }
	Vector3D operator -(int r) { return { x - r, y - r, z - r}; }

	Vector3D operator /(int r) { return { x / r, y / r, z / r}; }
};

struct Camera
{
	Vector2D project2D(Vector3D original);
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