#include "matrix.h"

#include <cmath>

#include "vector3d.h"

namespace Draw{

Matrix4x4::Matrix4x4()
{
	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			data[i][j] = 0;
		}
	}
}

Matrix4x4 Matrix4x4::Identity()
{
	Matrix4x4 m;
	for (int i=0; i<4; ++i) {
		m[i][i] = 1;
	}
	return m;
}

Matrix4x4 Matrix4x4::Translation(Vector3D position)
{
	Matrix4x4 m = Identity();
	m[0][3] = position.x;
	m[1][3] = position.y;
	m[2][3] = position.z;
	return m;
}

Matrix4x4 Matrix4x4::Scale(float factor)
{
	Matrix4x4 m = Identity();
	m[0][0] = factor;
	m[1][1] = factor;
	m[2][2] = factor;
	return m;
}

Matrix4x4 Matrix4x4::Perspective(float fieldOfViewDegrees, float aspectRatio)
{
	long double PI = 3.141592653589793238462643383279502884L;

	Matrix4x4 m{};
	m[1][1] = 1.0f / std::tan((PI / 180.0f) * fieldOfViewDegrees * 0.5f);
	m[0][0] = m[1][1] / aspectRatio;
	m[2][3] = +1.0f;
	m[3][2] = -1.0f;
	return m;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4& rhs)
{
	Matrix4x4 m{};
	for (int row=0; row<4; ++row) {
		for (int col=0; col<4; ++col) {
			for (int k=0; k<4; ++k) {
				m[row][col] += data[row][k] * rhs[k][col];
			}
		}
	}
	return m;
}

Vector3D Matrix4x4::operator*(Vector3D& rhs)
{
	Vector3D v{}; v[3]=0;
	for (int row=0; row<4; ++row) {
		for (int k=0; k<4; ++k) {
			v[row] += data[row][k] * rhs[k];
		}
	}
	return v;
}

std::ostream& operator<<(std::ostream& s , const Matrix4x4& m)
{
	s << "[" << m[0][0] << "," << m[0][1] << "," << m[0][2] << "," << m[0][3] << "\n";
	s << " " << m[1][0] << "," << m[1][1] << "," << m[1][2] << "," << m[1][3] << "\n";
	s << " " << m[2][0] << "," << m[2][1] << "," << m[2][2] << "," << m[2][3] << "\n";
	s << " " << m[3][0] << "," << m[3][1] << "," << m[3][2] << "," << m[3][3] << "]";
    return s;
}




}
