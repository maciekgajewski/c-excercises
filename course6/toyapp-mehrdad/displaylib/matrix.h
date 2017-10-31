#pragma once

#include "vector3d.h"

#include <array>

namespace Display {

struct Matrix4by4
{
	static const int ROW_COUNT = 4;
	static const int COL_COUNT = 4;

	Matrix4by4();

	std::array<std::array<double, COL_COUNT>, ROW_COUNT> mArray;
};

Matrix4by4 operator* (const Matrix4by4& m1, Matrix4by4 m2);
Vector3D operator* (const Matrix4by4& m, Vector3D v);

struct Matrix4by1
{
	static const int ROW_COUNT = 4;
	static const int COL_COUNT = 1;

	Matrix4by1();

	std::array<std::array<double, COL_COUNT>, ROW_COUNT> mArray;
};

Matrix4by1 Vector3DToMatrix(Vector3D v);
Vector3D MatrixToVector3D(Matrix4by1 m);

}
