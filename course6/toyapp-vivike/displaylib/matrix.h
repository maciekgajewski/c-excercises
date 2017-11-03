#pragma once

#include <cstdint>
#include <array>
#include <iostream>

#include "vector.h"

namespace Display {

class Matrix44
{
	std::array<std::array<float, 4>, 4> matrix;

public:
	Matrix44(): matrix{{0}} {};
	Matrix44(std::array<std::array<float, 4>, 4> newMatrix): matrix(newMatrix) {};;


	std::array<float, 4>& operator [](int element) 
	{ 
		return matrix[element];
	}

	const std::array<float, 4>& operator [](int element) const
	{
		return matrix[element];
	}

	Matrix44 operator*(const Matrix44& rhs) const;
	Vector3D operator*(const Vector3D& rhs) const;

	static Matrix44 Zero();
	static Matrix44 Eye();

	static Matrix44 Scale(float scaling);
	static Matrix44 Scale(Vector3D scaling);
	static Matrix44 Translate(Vector3D translation);
	static Matrix44 Rotate(Vector3D orientation);
 
};

std::ostream& operator <<(std::ostream& stream, Matrix44 mat);

}