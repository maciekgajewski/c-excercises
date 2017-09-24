#include "vector3d.h"
#include "transformation3d.h"

#include <cmath>

namespace Display {

Move3D::Move3D(Vector3D move) : Transformation3D()
{
	mMove = move;
}

Vector3D Move3D::Apply(Vector3D vertex) const
{
	return {
		vertex.x + mMove.x,
				vertex.y + mMove.y,
				vertex.z + mMove.z,
	};
}

Scale3D::Scale3D(Vector3D scale) : Transformation3D()
{
	mScale = scale;
}

Vector3D Scale3D::Apply(Vector3D vertex) const
{
	return {
		vertex.x * mScale.x,
				vertex.y * mScale.y,
				vertex.z * mScale.z,
	};
}

Rotate3D::Rotate3D(double thetaX, double thetaY, double thetaZ)
{
	mThetaX = thetaX;
	mThetaY = thetaY;
	mThetaZ = thetaZ;
}

Vector3D Rotate3D::Apply(Vector3D vertex) const
{
	return ApplyZ(ApplyY(ApplyX(vertex)));
}

Vector3D Rotate3D::ApplyX(Vector3D vertex) const
{
	return {
		vertex.x,
				std::cos(mThetaX) * vertex.y - std::sin(mThetaX) * vertex.z,
				std::sin(mThetaX) * vertex.y + std::cos(mThetaX) * vertex.z,
	};
}

Vector3D Rotate3D::ApplyY(Vector3D vertex) const
{
	return {
		std::cos(mThetaY) * vertex.x + std::sin(mThetaY) * vertex.z,
				vertex.y,
				- std::sin(mThetaY) * vertex.x + std::cos(mThetaY) * vertex.z,
	};
}

Vector3D Rotate3D::ApplyZ(Vector3D vertex) const
{
	return {
		std::cos(mThetaZ) * vertex.x - std::sin(mThetaZ) * vertex.y,
				std::sin(mThetaZ) * vertex.x + std::cos(mThetaZ) * vertex.y,
				vertex.z,
	};
}

}
