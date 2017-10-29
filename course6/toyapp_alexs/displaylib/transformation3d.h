#pragma once

#include "vector.h"
#include "matrix.h"

#include <array>

namespace Display {

class Transformation3D {
public:
	Transformation3D();
	Transformation3D(Matrix<4, 4> matrix);
	Transformation3D Combine(const Transformation3D& otherTransformation) const;
	Transformation3D WithRotation(double thetaX, double thetaY, double thetaZ) const;
	Transformation3D WithMoving(const Vector3D& vector) const;
	Transformation3D WithScaling(const Vector3D& vector) const;
	Vector3D Apply(const Vector3D& vector) const;
private:
	Matrix<4, 4> mMatrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
};

}
