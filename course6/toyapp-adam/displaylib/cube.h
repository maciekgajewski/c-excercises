#pragma once

#include "transform.h"

namespace Display {

class Matrix44;
class Surface3D;

class Cube
{
public:
	Transform transform;

	Cube(Vector3D center, float size, Color color);

	void Draw(Surface3D& surface, Matrix44& view) const;
private:
	Color mColor;
};

}
