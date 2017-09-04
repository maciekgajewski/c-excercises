#pragma once

#include "matrix.h"

namespace Math {

class Transform
{
public:
	Transform();

	void SetPosition(Vector3D position) { mPosition = position; }
	void SetScale(float size) { mScale = size; }
	void SetOrientation(Vector3D yawPitchRoll) { mOrientation = yawPitchRoll; }

	void Move(Vector3D delta) { mPosition += delta; }
	void Grow(float delta) { mScale += delta; }
	void Rotate(Vector3D yawPitchRoll) { mOrientation += yawPitchRoll; }

	Matrix44 CreateMatrix() const;
	Matrix44 CreateInverseMatrix() const;
private:
	Vector3D mPosition;
	Vector3D mOrientation;
	float mScale;
};

}
