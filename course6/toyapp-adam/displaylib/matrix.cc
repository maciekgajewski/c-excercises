#include "matrix.h"

namespace Display {

Matrix44::Matrix44()
{
	mMatrix[ 0] = 1; mMatrix[ 1] = 0; mMatrix[ 2] = 0; mMatrix[ 3] = 0;
	mMatrix[ 4] = 0; mMatrix[ 5] = 1; mMatrix[ 6] = 0; mMatrix[ 7] = 0;
	mMatrix[ 8] = 0; mMatrix[ 9] = 0; mMatrix[10] = 1; mMatrix[11] = 0;
	mMatrix[12] = 0; mMatrix[13] = 0; mMatrix[14] = 0; mMatrix[15] = 1;
}

void Matrix44::SetPosition(Vector3D vector)
{
	mMatrix[TRANSLATE_X] = vector.x;
	mMatrix[TRANSLATE_Y] = vector.y;
	mMatrix[TRANSLATE_Z] = vector.z;
}

void Matrix44::SetScale(float size)
{
	mMatrix[SCALE_X] = size;
	mMatrix[SCALE_Y] = size;
	mMatrix[SCALE_Z] = size;
}

Matrix44 Matrix44::operator*(const Matrix44& rhs) const
{
	Matrix44 result;
	for(int x = 0; x < 4; ++x) {
		for(int y = 0; y < 4; ++y) {
			const auto i = 4*x+y;
			result.mMatrix[i] = 0;
			for(int z = 0; z < 4; ++z) {
				result.mMatrix[i] += mMatrix[4*x+z] * rhs.mMatrix[4*z+y];
			}
		}
	}
	return result;
}

Vector3D Matrix44::operator*(const Vector3D& rhs) const
{
	return {
		rhs.x * mMatrix[ 0] + rhs.y * mMatrix[ 4] + rhs.z * mMatrix[ 8] + mMatrix[12],
		rhs.x * mMatrix[ 1] + rhs.y * mMatrix[ 5] + rhs.z * mMatrix[ 9] + mMatrix[13],
		rhs.x * mMatrix[ 2] + rhs.y * mMatrix[ 6] + rhs.z * mMatrix[10] + mMatrix[14]
	};
}

}
