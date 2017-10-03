#include "transformation3d.h"

#include <cmath>

namespace Display {

Transformation3D::Transformation3D()
	: mMatrix({
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
})
{
}

Transformation3D::Transformation3D(Matrix<4, 4> matrix)
	: mMatrix(matrix)
{
}

Transformation3D::Transformation3D(std::array<std::array<double, 4>, 4> matrix)
	: mMatrix(matrix)
{
}

Transformation3D Transformation3D::Combine(const Transformation3D& otherTransformation) const
{
	return {
		this->mMatrix * otherTransformation.mMatrix
	};
}

Transformation3D Transformation3D::WithRotation(double thetaX, double thetaY, double thetaZ) const
{
	Transformation3D transformationX
	{
		{
			1, 0, 0, 0,
			0, std::cos(thetaX), -std::sin(thetaX), 0,
			0, std::sin(thetaX), std::cos(thetaX), 0,
			0, 0, 0, 1
		}
	};
	Transformation3D transformationY
	{
		{
			std::cos(thetaY), 0, std::sin(thetaY), 0,
			0, 1, 0, 0,
			-std::sin(thetaY), 0, std::cos(thetaY), 0,
			0, 0, 0, 1
		}
	};
	Transformation3D transformationZ
	{
		{
			std::cos(thetaZ), -std::sin(thetaZ), 0, 0,
			std::sin(thetaZ), std::cos(thetaZ), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		}
	};
	return Combine(transformationX)
			.Combine(transformationY)
			.Combine(transformationZ);
}

Transformation3D Transformation3D::WithMoving(const Vector<double, 3>& vector) const
{
	Transformation3D transformation
	{
		{
			1,0,0,vector.x,
			0,1,0,vector.y,
			0,0,1,vector.z,
			0,0,0,1
		}
	};
	return Combine(transformation);
}

Transformation3D Transformation3D::WithScaling(const Vector<double, 3>& vector) const
{
	Transformation3D transformation
	{
		{
			vector.x, 0, 0, 0,
			0, vector.y, 0, 0,
			0, 0, vector.z, 0,
			0, 0, 0, 1
		}
	};
	return Combine(transformation);
}

Vector<double, 3> Transformation3D::Apply(const Vector<double, 3>& vector) const
{
	Matrix<4, 1> vMatrix {{
		vector.x,
		vector.y,
		vector.z,
		1
	}};

	Matrix<4, 1> result = mMatrix * vMatrix;

	return {
		result[0][0],
		result[1][0],
		result[2][0]
	};
}

}
