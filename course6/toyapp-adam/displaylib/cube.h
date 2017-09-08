#pragma once

#include "color.h"
#include "math/transform.h"

namespace Math {
	struct Matrix44;
}

namespace Display {

class Surface3D;
using Math::Matrix44;
using Math::Transform;
using Math::Vector3D;

class Cube
{
public:
	Transform transform;

	Cube(Vector3D center, float size, Color fillColor, Color edgeColor);

	void Draw(Surface3D& surface, const Matrix44& view) const;
private:
	Color mFillColor;
	Color mEdgeColor;
};

}
