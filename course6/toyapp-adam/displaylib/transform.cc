#include "transform.h"

namespace Display {

Transform::Transform()
:	mScale(1.0f)
{}

void Transform::SetPosition(Vector3D position)
{
	mPosition = position;
}

void Transform::SetScale(float size)
{
	mScale = size;
}

void Transform::Move(Vector3D position)
{
	mPosition += position;
}

Matrix44 Transform::CreateMatrix() const
{
	Matrix44 scale, translate;
	scale.SetScale(mScale);
	translate.SetPosition(mPosition);
	return translate * scale;
}

Matrix44 Transform::CreateInverseMatrix() const
{
	Matrix44 translate;
	translate.SetPosition(-mPosition);
	return translate;
}

}
