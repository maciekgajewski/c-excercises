#pragma once

#include "vector.h"

namespace Math {

class Triangle2D
{
public:
	Triangle2D(Vector2D pointA, Vector2D pointB, Vector2D pointC)
	{
		mPoints[0] = pointA;
		mPoints[1] = pointB;
		mPoints[2] = pointC;
	}

	Vector2D& operator[](unsigned index) { return mPoints[index]; }
	Vector2D operator[](unsigned index) const { return mPoints[index]; }
private:
	Vector2D mPoints[3];
};

class Triangle3D
{
public:
	Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC)
	{
		mPoints[0] = pointA;
		mPoints[1] = pointB;
		mPoints[2] = pointC;
	}

	Vector3D& operator[](unsigned index) { return mPoints[index]; }
	Vector3D operator[](unsigned index) const { return mPoints[index]; }

	Vector3D GetSurfaceNormal() const
	{
		return (mPoints[1] - mPoints[0]).Cross(mPoints[2] - mPoints[0]).Normalized();
	}
private:
	Vector3D mPoints[3];
};

}
