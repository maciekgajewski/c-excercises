#include "matrix.h"

namespace Math {

Matrix44 Matrix44::Identity()
{
	Matrix44 m;

	m.mMatrix[ 0] = 1.0f; m.mMatrix[ 1] = 0.0f; m.mMatrix[ 2] = 0.0f; m.mMatrix[ 3] = 0.0f;
	m.mMatrix[ 4] = 0.0f; m.mMatrix[ 5] = 1.0f; m.mMatrix[ 6] = 0.0f; m.mMatrix[ 7] = 0.0f;
	m.mMatrix[ 8] = 0.0f; m.mMatrix[ 9] = 0.0f; m.mMatrix[10] = 1.0f; m.mMatrix[11] = 0.0f;
	m.mMatrix[12] = 0.0f; m.mMatrix[13] = 0.0f; m.mMatrix[14] = 0.0f; m.mMatrix[15] = 1.0f;

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

Matrix44 Matrix44::Scale(float size)
{
	Matrix44 m = Identity();

	m.mMatrix[SCALE_X] = size;
	m.mMatrix[SCALE_Y] = size;
	m.mMatrix[SCALE_Z] = size;

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

}
