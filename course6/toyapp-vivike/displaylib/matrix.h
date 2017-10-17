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
	Matrix44(std::array<std::array<float, 4>, 4> newMatrix);


	std::array<float, 4>& operator [](int element) 
	{ 
		return matrix[element];
	}

	const std::array<float, 4>& operator [](int element) const
	{
		return matrix[element];
	}

	Matrix44 Zero();
	Matrix44 Eye();
};

}