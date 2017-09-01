#pragma once

#include "matrix.h"

namespace Display {

class Transform
{
public:
	void SetPosition(Vector3D position);
	Matrix44 CreateMatrix() const;
private:
	Vector3D mPosition;
};

}
