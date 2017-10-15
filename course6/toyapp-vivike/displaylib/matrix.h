#pragma once

#include <cstdint>
#include <array>
#include <iostream>

#include "vector.h"

namespace Display {

template<typename T, int rows, int cols>
class Matrix
{
	std::array<std::array<T, cols>, rows> matrix;

public:
	Matrix(): matrix{{0}} {};
	Matrix(std::array<std::array<T, cols>, rows> newMatrix);

	T operator [](MatrixElement location) 
	{ 
		return this->matrix[location[0]][location[1]];
	}

};

}