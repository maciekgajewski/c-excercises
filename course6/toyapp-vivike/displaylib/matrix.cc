#include "matrix.h"

#include <SDL2/SDL.h>

namespace Display {


Matrix44 Matrix44::Zero()
{
	Matrix44 m;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			m[i][j] = 0.0f;
		}
	}

	return m;
}

Matrix44 Matrix44::Eye()
{
	Matrix44 m = Matrix44::Zero();

	for(int i = 0; i < 4; i++)
	{
		m[i][i] = 1.0f;
	
	}

	return m;
}

Matrix44 Matrix44::operator*(const Matrix44& rhs) const
{
	Matrix44 result;

	for(int row = 0; row < 4; ++row) {
		for(int col = 0; col < 4; ++col) {
			result[row][col] = 0;
			for(int z = 0; z < 4; ++z) {
				result[row][col] += matrix[row][z] * rhs[z][col];
			}
		}
	}

	return result;
}


}