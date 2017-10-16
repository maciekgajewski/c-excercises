#pragma once

#include "color.h"
#include "math/transform.h"
#include "math/triangle.h"
#include <vector>

namespace Display {

struct Mesh
{
	std::vector<Math::Triangle3D> triangles;
	Math::Transform transform;
	Color fillColor;
	Color edgeColor;

	void NormalizeScale();
};

}
