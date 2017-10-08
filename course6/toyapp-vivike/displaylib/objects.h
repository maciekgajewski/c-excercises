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

	Vector operator +(Vector& b) 
	{ 
		Vector newVec;
		for(int i=0; i<length; i++)
		{
			newVec.vec[i] = this->vec[i] + b.vec[i];
		}
		return newVec;
	}

	Vector operator *(int b) 
	{ 
		Vector newVec;
		for(int i=0; i<length; i++)
		{
			newVec.vec[i] = this->vec[i] * b;
		}
		return newVec;
	}

	Vector operator -(Vector& r) 
	{ 
		Vector newVec;
		for(int i=0; i<length; i++)
		{
			newVec.vec[i] = this->vec[i] - r.vec[i];
		}
		return newVec;
	}

	Vector operator /(int r) 
	{ 
		Vector newVec;
		for(int i=0; i<length; i++)
		{
			newVec.vec[i] = this->vec[i] / r;
		}
		return newVec;
	}	

};

template<typename T, int length>
std::ostream& operator <<(std::ostream& stream, Vector<T, length> vec) 
{ 
	for(int i=0; i<length; i++)
	{
		stream << vec.vec[i] << ", ";
	}
	return stream;
}


using Pixel = Vector<int, 2>;
using Vector3D = Vector<float, 3>;

struct Camera
{
	Pixel project2D(Vector3D& original);
};

struct Rectangle
{
	Vector3D corner1;
	Vector3D corner2;
	Vector3D corner3;
	Vector3D corner4;

	Rectangle move(Vector3D&);
};

}