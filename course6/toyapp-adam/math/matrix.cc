#include "matrix.h"

#include <cmath>

namespace Math {

namespace {
	constexpr auto PI = std::atan(1.0) * 4.0;
	const auto TRANSLATE_X = 3;
	const auto TRANSLATE_Y = 7;
	const auto TRANSLATE_Z = 11;
	const auto SCALE_X = 0;
	const auto SCALE_Y = 5;
	const auto SCALE_Z = 10;
}

Matrix44 Matrix44::Zero()
{
	Matrix44 m;

	for(auto& element : m.mMatrix)
		element = 0.0f;

	return m;
}

Matrix44 Matrix44::Identity()
{
	Matrix44 m = Zero();

	m.mMatrix[SCALE_X] = 1.0f;
	m.mMatrix[SCALE_Y] = 1.0f;
	m.mMatrix[SCALE_Z] = 1.0f;
	m.mMatrix[15] = 1.0f;

	return m;
}

Matrix44 Matrix44::Translation(Vector3D position)
{
	Matrix44 m = Identity();

	m.mMatrix[TRANSLATE_X] = position[0];
	m.mMatrix[TRANSLATE_Y] = position[1];
	m.mMatrix[TRANSLATE_Z] = position[2];

	return m;
}

Matrix44 Matrix44::Rotation(Vector3D yawPitchRoll)
{
	Matrix44 m = Zero();

	float ch = std::cos(yawPitchRoll[0]);
	float sh = std::sin(yawPitchRoll[0]);
	float cp = std::cos(yawPitchRoll[1]);
	float sp = std::sin(yawPitchRoll[1]);
	float cb = std::cos(yawPitchRoll[2]);
	float sb = std::sin(yawPitchRoll[2]);

	m.mMatrix[ 0] =  ch * cb + sh * sp * sb;
	m.mMatrix[ 1] = -ch * sb + sh * sp * cb;
	m.mMatrix[ 2] =  sh * cp;
	m.mMatrix[ 4] =  sb * cp;
	m.mMatrix[ 5] =  cb * cp;
	m.mMatrix[ 6] = -sp;
	m.mMatrix[ 8] = -sh * cb + ch * sp * sb;
	m.mMatrix[ 9] =  sb * sh + ch * sp * cb;
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
	Matrix44 result;

	for(unsigned x = 0; x < 4; ++x) {
		auto row = x * 4;
		for(unsigned y = 0; y < 4; ++y) {
			auto i = y + row;
			result.mMatrix[i] = 0;
			for(unsigned z = 0; z < 4; ++z) {
				result.mMatrix[i] += mMatrix[z + row] * rhs.mMatrix[y + z * 4];
			}
		}
	}

	return result;
}

Vector3D Matrix44::operator*(const Vector3D& rhs) const
{
	return {
		rhs[0] * mMatrix[ 0] + rhs[1] * mMatrix[ 1] + rhs[2] * mMatrix[ 2] + mMatrix[3],
		rhs[0] * mMatrix[ 4] + rhs[1] * mMatrix[ 5] + rhs[2] * mMatrix[ 6] + mMatrix[7],
		rhs[0] * mMatrix[ 8] + rhs[1] * mMatrix[ 9] + rhs[2] * mMatrix[10] + mMatrix[11]
	};
}

Vector4D Matrix44::operator*(const Vector4D& rhs) const
{
	return {
		rhs[0] * mMatrix[ 0] + rhs[1] * mMatrix[ 1] + rhs[2] * mMatrix[ 2] + mMatrix[ 3],
		rhs[0] * mMatrix[ 4] + rhs[1] * mMatrix[ 5] + rhs[2] * mMatrix[ 6] + mMatrix[ 7],
		rhs[0] * mMatrix[ 8] + rhs[1] * mMatrix[ 9] + rhs[2] * mMatrix[10] + mMatrix[11],
		rhs[0] * mMatrix[12] + rhs[1] * mMatrix[13] + rhs[2] * mMatrix[14] + mMatrix[15]
	};
}

}
