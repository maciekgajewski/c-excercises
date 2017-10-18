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

	static Matrix44 Zero();
	static Matrix44 Eye();
};

/*std::ostream& operator <<(std::ostream& stream, Matrix44 mat) 
{ 
	for(int row=0; row<4; row++)
	{
		for(int col=0; col<4; col++)
		{
			stream << mat[row][col] << ", ";
		}
		stream << std::endl;
	}
	return stream;
}*/

}