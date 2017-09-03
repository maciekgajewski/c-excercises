#include "transform.h"

namespace Math {

Transform::Transform()
:	mScale(1.0f)
{}

Matrix44 Transform::CreateMatrix() const
{
	return Matrix44::Translation(mPosition) *
	       Matrix44::Scale(mScale) *
	       Matrix44::Rotation(mOrientation.x, mOrientation.y, mOrientation.z);
}

Matrix44 Transform::CreateInverseMatrix() const
{
	// @todo remember to mutiply in reversed order!
	return Matrix44::Translation(-mPosition);
}

}
