#pragma once

#include "vector_common.h"

#include <array>

namespace Display {

class Triangle
{
private:
	std::array<Vector3D, 3> mVertex;
public:
	Vector3D& operator[] (int i) { return mVertex[i]; }
	const Vector3D& operator[] (int i) const { return mVertex[i]; }

	Triangle(Vector3D v1, Vector3D v2, Vector3D v3)
		: mVertex{ v1, v2, v3 }
	{}
};
}