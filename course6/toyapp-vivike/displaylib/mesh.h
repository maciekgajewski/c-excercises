#pragma once

#include "objects.h"
#include "matrix.h"
#include "../math/transform.h"
#include <vector>

namespace Display {

struct Mesh
{
	std::vector<Triangle> triangles;
	Math::Transform transform;
	Color fillColor;
	Color edgeColor;

	void NormalizeScale();
};

}