#pragma once

#include "vector3d.h"

#include <array>

namespace Display {

	class Triangle
	{
	private:
		std::array<Vector3D,3> _vertex;
	public:
		Vector3D& operator[] (int i) { return _vertex[i]; }
		const Vector3D& operator[] (int i) const { return _vertex[i]; }
	};
}