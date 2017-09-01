#pragma once

#include "vector.h"

namespace Display {

class Matrix44
{
public:
	Matrix44();

	void Translate(Vector3D vector);

	Matrix44 operator*(const Matrix44& other) const;
	Vector3D operator*(const Vector3D& other) const;
private:
	static constexpr auto TRANSLATE_X = 12;
	static constexpr auto TRANSLATE_Y = 13;
	static constexpr auto TRANSLATE_Z = 14;

	float mMatrix[16];
};

}
