#pragma once

#include "matrix.h"

namespace Display {

class Transform
{
public:
	Transform();

	void SetPosition(Vector3D position);
	void SetScale(float size);

	void Move(Vector3D position);

	Matrix44 CreateMatrix() const;
	Matrix44 CreateInverseMatrix() const;
private:
	Vector3D mPosition;
	float mScale;
};

}
