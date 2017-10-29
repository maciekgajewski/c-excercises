#pragma once

#include <array>

namespace Display
{
template<class T, std::size_t S>
struct Vector
{
public:
	template<class... E>
	Vector(E... data)
		: mData {static_cast<T>(data)...}
	{
	}

	T& operator [](int index)
	{
		return mData[index];
	}
private:
	std::array<T, S> mData;
};

struct Pixel: public Vector<int, 2>
{
	Pixel()
		: Vector(),
		  x((*this)[0]),
		  y((*this)[1])
	{}

	Pixel(int x, int y)
		: Vector(x, y),
		  x((*this)[0]),
		  y((*this)[1])
	{}

	Pixel& operator =(const Pixel& other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	int& x;
	int& y;
};

struct Vector3D: Vector<double, 3>
{
	Vector3D()
		: Vector(),
		  x((*this)[0]),
		  y((*this)[1]),
		  z((*this)[2])
	{}

	Vector3D(double x, double y, double z)
		: Vector(x, y, z),
		  x((*this)[0]),
		  y((*this)[1]),
		  z((*this)[2])
	{}

	Vector3D& operator =(const Vector3D& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}

	double& x;
	double& y;
	double& z;
};

}
