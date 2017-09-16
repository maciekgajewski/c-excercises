#include "matrix.h"

#include <cmath>

namespace Math {

namespace {
	constexpr auto PI = 3.14159265359; //std::atan(1.0) * 4.0;
}

Matrix44 Matrix44::Zero()
{
	Matrix44 m;

	for(unsigned i = 0; i < 16; ++i)
		m.mMatrix[i] = 0.0f;

	return m;
}

Matrix44 Matrix44::Identity()
{
	Matrix44 m = Zero();

	m.mMatrix[ 0] = 1.0f;
	m.mMatrix[ 5] = 1.0f;
	m.mMatrix[10] = 1.0f;
	m.mMatrix[15] = 1.0f;

	return m;
}

Matrix44 Matrix44::Translation(Vector3D position)
{
	Matrix44 m = Identity();

	m.mMatrix[TRANSLATE_X] = position.x;
	m.mMatrix[TRANSLATE_Y] = position.y;
	m.mMatrix[TRANSLATE_Z] = position.z;

	return m;
}

Matrix44 Matrix44::Rotation(Vector3D yawPitchRoll)
{
	Matrix44 m = Zero();

	const float ch = std::cos(yawPitchRoll.x);
	const float sh = std::sin(yawPitchRoll.x);
	const float cp = std::cos(yawPitchRoll.y);
	const float sp = std::sin(yawPitchRoll.y);
	const float cb = std::cos(yawPitchRoll.z);
	const float sb = std::sin(yawPitchRoll.z);

	const float shsp = sh * sp;
	const float chsp = ch * sp;

	m.mMatrix[ 0] =  ch * cb + shsp * sb;
	m.mMatrix[ 1] = -ch * sb + shsp * cb;
	m.mMatrix[ 2] =  sh * cp;
	m.mMatrix[ 4] =  sb * cp;
	m.mMatrix[ 5] =  cb * cp;
	m.mMatrix[ 6] = -sp;
	m.mMatrix[ 8] = -sh * cb + chsp * sb;
	m.mMatrix[ 9] =  sb * sh + chsp * cb;
	m.mMatrix[10] =  ch * cp;
	m.mMatrix[15] =  1.0f;

	return m;
}

Matrix44 Matrix44::Scale(float size)
{
	Matrix44 m = Identity();

	m.mMatrix[SCALE_X] = size;
	m.mMatrix[SCALE_Y] = size;
	m.mMatrix[SCALE_Z] = size;

	return m;
}

Matrix44 Matrix44::Perspective(float fieldOfViewDegrees, float aspectRatio)
{
	Matrix44 m = Zero();

	m.mMatrix[SCALE_Y] = 1.0f / std::tan((PI / 180.0f) * fieldOfViewDegrees * 0.5f);
	m.mMatrix[SCALE_X] = m.mMatrix[SCALE_Y] / aspectRatio;
	m.mMatrix[11] = +1.0f;
	m.mMatrix[14] = -1.0f;

	return m;
}

Matrix44 Matrix44::operator*(const Matrix44& rhs) const
{
	constexpr unsigned ROWS = 4;
	constexpr unsigned COLS = 4;

	Matrix44 result;

	for(unsigned x = 0; x < ROWS; ++x) {
		const unsigned row = x * ROWS;
		for(unsigned y = 0; y < COLS; ++y) {
			const unsigned i = y + row;
			result.mMatrix[i] = 0;
			for(unsigned z = 0; z < ROWS; ++z) {
				result.mMatrix[i] += mMatrix[z + row] * rhs.mMatrix[y + z * ROWS];
			}
		}
	}

	return result;
}

Vector3D Matrix44::operator*(const Vector3D& rhs) const
{
	return {
		rhs.x * mMatrix[ 0] + rhs.y * mMatrix[ 1] + rhs.z * mMatrix[ 2] + mMatrix[3],
			rhs.x * mMatrix[ 4] + rhs.y * mMatrix[ 5] + rhs.z * mMatrix[ 6] + mMatrix[7],
			rhs.x * mMatrix[ 8] + rhs.y * mMatrix[ 9] + rhs.z * mMatrix[10] + mMatrix[11]
	};
}

Vector4D Matrix44::operator*(const Vector4D& rhs) const
{
	return {
		rhs.x * mMatrix[ 0] + rhs.y * mMatrix[ 1] + rhs.z * mMatrix[ 2] + mMatrix[ 3],
			rhs.x * mMatrix[ 4] + rhs.y * mMatrix[ 5] + rhs.z * mMatrix[ 6] + mMatrix[ 7],
			rhs.x * mMatrix[ 8] + rhs.y * mMatrix[ 9] + rhs.z * mMatrix[10] + mMatrix[11],
			rhs.x * mMatrix[12] + rhs.y * mMatrix[13] + rhs.z * mMatrix[14] + mMatrix[15]
	};
}

}
