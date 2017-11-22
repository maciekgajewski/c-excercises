#include "matrix.h"

#include <cmath>

#include <SDL2/SDL.h>

namespace Display {

namespace {
	constexpr auto PI = std::atan(1.0) * 4.0;
}

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

Matrix44 Matrix44::Perspective(float fieldOfViewDegrees, float aspectRatio)
{
	Matrix44 m = Matrix44::Zero();

	m[1][1] = 1.0f / std::tan((PI / 180.0f) * fieldOfViewDegrees * 0.5f);
	m[0][0] = m[1][1] / aspectRatio;
	m[2][3] = +1.0f;
	m[3][2] = -1.0f;

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

Matrix44 Matrix44::Rotate(Vector3D orientation)
{
	Matrix44 m = Matrix44::Zero();

	float c1 = std::cos(orientation[0]);
	float s1 = std::sin(orientation[0]);
	float c2 = std::cos(orientation[1]);
	float s2 = std::sin(orientation[1]);
	float c3 = std::cos(orientation[2]);
	float s3 = std::sin(orientation[2]);

	m[0][0] = c1 * c3 + s1 * s2 * s3;
	m[0][1] = -c1 * s3 + s1 * s2 * c3;
	m[0][2] = s1 * c2;
	m[1][0] = s3 * c2;
	m[1][1] = c3 * c2;
	m[1][2] = -s2;
	m[2][0] = -s1 * c3 + c1 * s2 * s3;
	m[2][1] = s3 * s1 + c1 * s2 * c3;
	m[2][2] = c1 * c2;
	m[3][3] = 1.0f;

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

Vector<float, 4> Matrix44::operator*(const Vector<float, 4>& rhs) const
{
	std::array<float, 4> result;

	for(int row = 0; row < 4; ++row) {
		result[row] = 0;
		for(int col = 0; col < 4; ++col) {
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