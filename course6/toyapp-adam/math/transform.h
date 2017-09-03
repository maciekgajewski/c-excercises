#pragma once

#include "matrix.h"

namespace Math {

class Transform
{
public:
	Transform();

	void SetPosition(Vector3D position) { mPosition = position; }
	void SetScale(float size) { mScale = size; }
	void SetOrientation(Vector3D eulerAngles) { /* @todo */ }

	void Move(Vector3D delta) { mPosition += delta; }
	void Grow(float delta) { mScale += delta; }
	void Rotate(Vector3D delta) { /* @todo */ }

	Matrix44 CreateMatrix() const;
	Matrix44 CreateInverseMatrix() const;
private:
	Vector3D mPosition;
	float mScale;
};

}
