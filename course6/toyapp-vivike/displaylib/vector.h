#pragma once

#include <cstdint>
#include <array>
#include <iostream>
#include <cmath>

namespace Display {

template<typename T, int size>
class Vector
{
	std::array<T, size> vec;

public:
	Vector(): vec{{0}} {};
	Vector(std::array<T, size> newvec): vec(newvec) {};

	Vector operator +(Vector b) 
	{ 
		Vector newVec;
		for(int i=0; i<size; i++)
		{
			newVec.vec[i] = this->vec[i] + b.vec[i];
		}
		return newVec;
	}

	Vector operator *(float b) 
	{ 
		Vector newVec;
		for(int i=0; i<size; i++)
		{
			newVec.vec[i] = this->vec[i] * b;
		}
		return newVec;
	}

	Vector operator -(Vector r) 
	{ 
		Vector newVec;
		for(int i=0; i<size; i++)
		{
			newVec.vec[i] = this->vec[i] - r.vec[i];
		}
		return newVec;
	}

	Vector operator /(int r) 
	{ 
		Vector newVec;
		for(int i=0; i<size; i++)
		{
			newVec.vec[i] = this->vec[i] / r;
		}
		return newVec;
	}	

	T operator [](int elem) 
	{ 
		return this->vec[elem];
	}

	const T operator [](int elem) const
	{ 
		return this->vec[elem];
	}

	Vector& operator=(const Vector& other)
	{
		for (unsigned i = 0; i < size; ++i)
			vec[i] = other[i];
		return *this;
	}

	float length();
	T dot(Vector<T, size>);
	//Vector<T, size> cross(Vector<T, size>);
};

template<typename T, int size>
std::ostream& operator <<(std::ostream& stream, Vector<T, size> vec) 
{ 
	for(int i=0; i<size; i++)
	{
		stream << vec[i] << ", ";
	}
	return stream;
}

template<typename T, int size>
float Vector<T, size>::length()
{
	float result = 0;
	for(auto x : this->vec)
	{
		result += x * x;
	}
	return sqrt(result);
}

template<typename T, int size>
T Vector<T, size>::dot(Vector<T, size> vecb)
{
	float result = 0;
	for(int i=0; i<size; i++)
	{
		result += this->vec[i] * vecb[i];
	}
	return result;
}

using Pixel = Vector<int, 2>;
using MatrixElement = Vector<int, 2>;
using Vector3D = Vector<float, 3>;

/* Don't think I want to go through the effort of implementing this, since it only works in 3D.
Vector3D Vector3D::dot(Vector3D vecr)
{
	Vector3D result;
	result[0] = this->vec[1] * vecr[2] - this->vec[2] * vecr[1];
	result[1] = this->vec[2] * vecr[0] - this->vec[0] * vecr[2];
	result[2] = this->vec[1] * vecr[1] - this->vec[1] * vecr[0];
	
	return result;
}*/

}