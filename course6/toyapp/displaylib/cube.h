#pragma once

#include "vector.h"

namespace Display {

struct Cube
{
	static constexpr unsigned VERTEX_COUNT = 8;

	Vector3D vertices[VERTEX_COUNT];

	Cube(Vector3D center, float size);
};

}
