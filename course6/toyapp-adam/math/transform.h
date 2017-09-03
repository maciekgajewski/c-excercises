#pragma once

#include "matrix.h"

namespace Math {

class Transform
{
public:
	Transform();

	void SetPosition(Vector3D position) { mPosition = position; }
	void SetScale(float size) { mScale = size; }
	void SetOrientation(float yaw, float pitch, float roll) { mOrientation = {yaw, pitch, roll}; }

	void Move(Vector3D delta) { mPosition += delta; }
	void Grow(float delta) { mScale += delta; }
	void Rotate(float yaw, float pitch, float roll) { mOrientation += {yaw, pitch, roll}; }

	Matrix44 CreateMatrix() const;
	Matrix44 CreateInverseMatrix() const;
private:
	Vector3D mPosition;
	Vector3D mOrientation;
	float mScale;
};

}
