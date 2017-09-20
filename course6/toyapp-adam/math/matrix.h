#pragma once

#include "vector.h"

namespace Math {

class Matrix44
{
public:
	static Matrix44 Zero();
	static Matrix44 Identity();
	static Matrix44 Translation(Vector3D position);
	static Matrix44 Rotation(Vector3D yawPitchRoll);
	static Matrix44 Scale(float size);
	static Matrix44 Perspective(float fieldOfViewDegrees, float aspectRatio);

	Matrix44 operator*(const Matrix44& rhs) const;
	Vector3D operator*(const Vector3D& rhs) const;
	Vector4D operator*(const Vector4D& rhs) const;
private:
	Matrix44() {}

	float mMatrix[4 * 4];
};

}
