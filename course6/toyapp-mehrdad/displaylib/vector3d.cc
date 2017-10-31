#include "vector3d.h"

namespace Display {

Vector3D operator+(Display::Vector3D v1, Display::Vector3D v2)
{
	return{v1.mX + v2.mX, v1.mY + v2.mY, v1.mZ + v2.mZ};
}

Vector3D operator-(Vector3D v1, Vector3D v2)
{
	return{v1.mX - v2.mX, v1.mY - v2.mY, v1.mZ - v2.mZ};
}

Vector3D operator+(Vector3D v1, double scalar)
{
	return{v1.mX + scalar, v1.mY + scalar, v1.mZ + scalar};
}

Vector3D operator-(Vector3D v1, double scalar)
{
	return{v1.mX - scalar, v1.mY - scalar, v1.mZ - scalar};
}

Vector3D operator*(Vector3D v1, double scalar)
{
	return{v1.mX * scalar, v1.mY * scalar, v1.mZ * scalar};
}

Vector3D operator/(Vector3D v1, double scalar)
{
	return{v1.mX / scalar, v1.mY / scalar, v1.mZ / scalar};
}

}

