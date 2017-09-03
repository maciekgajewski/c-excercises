#pragma once

#include "vector.h"

namespace Math {

class Matrix44
{
public:
	static Matrix44 Zero();
	static Matrix44 Identity();
	static Matrix44 Translation(Vector3D position);
	static Matrix44 Rotation(float yaw, float pitch, float roll);
	static Matrix44 Scale(float size);

	Matrix44 operator*(const Matrix44& rhs) const;
	Vector3D operator*(const Vector3D& rhs) const;
private:
	// this is a row-major matrix
	static constexpr auto TRANSLATE_X = 3;
	static constexpr auto TRANSLATE_Y = 7;
	static constexpr auto TRANSLATE_Z = 11;
	static constexpr auto SCALE_X = 0;
	static constexpr auto SCALE_Y = 5;
	static constexpr auto SCALE_Z = 10;

	Matrix44() {}

	float mMatrix[4 * 4];
};

}
