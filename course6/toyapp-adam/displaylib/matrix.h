#pragma once

#include "vector.h"

namespace Display {

class Matrix44
{
public:
	Matrix44();

	void SetPosition(Vector3D vector);
	void SetScale(float size);

	Matrix44 operator*(const Matrix44& rhs) const;
	Vector3D operator*(const Vector3D& rhs) const;
private:
	static constexpr auto TRANSLATE_X = 12;
	static constexpr auto TRANSLATE_Y = 13;
	static constexpr auto TRANSLATE_Z = 14;
	static constexpr auto SCALE_X = 0;
	static constexpr auto SCALE_Y = 5;
	static constexpr auto SCALE_Z = 10;

	float mMatrix[16];
};

}
