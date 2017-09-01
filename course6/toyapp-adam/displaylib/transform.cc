#include "transform.h"

namespace Display {

void Transform::SetPosition(Vector3D position)
{
	mPosition = position;
}

Matrix44 Transform::CreateMatrix() const
{
	Matrix44 matrix;
	matrix.Translate(mPosition);
	return matrix;
}

}
