#pragma once

#include "transform.h"

namespace Display {

class Matrix44;

class Cube
{
public:
	Transform transform;

	Cube(Vector3D center, float size);

	void Draw(Surface3D& surface, Matrix44& view, Color color) const;
private:
	Vector3D mCenter;
	float mHalfSize;
};

}
