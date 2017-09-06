#include "transform.h"

namespace Math {

Matrix44 Transform::CreateMatrix() const
{
	return Matrix44::Translation(mPosition) *
	       Matrix44::Scale(mScale) *
	       Matrix44::Rotation(mOrientation);
}

Matrix44 Transform::CreateInverseMatrix() const
{
	return Matrix44::Rotation(-mOrientation) *
	       Matrix44::Translation(-mPosition);
}

}
