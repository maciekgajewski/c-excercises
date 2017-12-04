#include "../displaylib/matrix.h"
#include "transform.h"

#include <cmath>

using namespace Display;

namespace Math {

Matrix44 Transform::CreateMatrix() const
{
	return Matrix44::Translate(mPosition) *
	       Matrix44::Scale(mScale) *
	       Matrix44::Rotate(mOrientation);
}

Matrix44 Transform::CreateInverseMatrix() const
{
	return Matrix44::Rotate(-mOrientation) *
	       Matrix44::Translate(-mPosition);
}

}
