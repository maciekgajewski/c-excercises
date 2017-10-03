#pragma once

#include "vector.h"
#include "matrix.h"

#include <array>

namespace Display {

class Transformation3D {
public:
	Transformation3D();
	Transformation3D(Matrix<4, 4> matrix);
	Transformation3D(std::array<std::array<double, 4>, 4> matrix);
	Transformation3D Combine(const Transformation3D& otherTransformation) const;
	Transformation3D WithRotation(double thetaX, double thetaY, double thetaZ) const;
	Transformation3D WithMoving(const Vector<double, 3>& vector) const;
	Transformation3D WithScaling(const Vector<double, 3>& vector) const;
	Vector<double, 3> Apply(const Vector<double, 3>& vector) const;
private:
	Matrix<4, 4> mMatrix
	{
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		}
	};
};

}
