#pragma once

#include "color.h"
#include "math/matrix.h"
#include "math/transform.h"

namespace Display {

class Surface3D;
using Math::Matrix44;
using Math::Transform;
using Math::Vector3D;

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
