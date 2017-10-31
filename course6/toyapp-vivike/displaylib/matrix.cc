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

Matrix44 Matrix44::Scale(float scaling)
{
	Matrix44 m = Matrix44::Zero();

	for(int i = 0; i < 4; i++)
	{
		m[i][i] = scaling;
	}

	return m;
}

Matrix44 Matrix44::Scale(Vector3D scaling)
{
	Matrix44 m = Matrix44::Eye();

	for(int i = 0; i < 3; i++)
	{
		m[i][i] = scaling[i];
	}

	return m;
}

Matrix44 Matrix44::Translate(Vector3D translation)
{
	Matrix44 m = Matrix44::Eye();

	for(int i = 0; i < 3; i++)
	{
		m[i][3] = translation[i];
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

Vector3D Matrix44::operator*(const Vector3D& rhs) const
{
	std::array<float, 3> result;

	for(int row = 0; row < 3; ++row) {
		result[row] = 0;
		for(int col = 0; col < 3; ++col) {
			result[row] += matrix[row][col] * rhs[col];
		}
		result[row] += matrix[row][3];
	}

	return result;
}

std::ostream& operator <<(std::ostream& stream, Matrix44 mat) 
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
}

}