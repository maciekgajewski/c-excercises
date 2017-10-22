#pragma once

#include <array>

#include "surface3d.h"
#include "color.h"
#include "transformation3d.h"
#include "vector.h"

namespace Display {

class Cube {
public:
	Cube(Color color);
	void Draw(Surface3D& surface) const;
	Cube Transform(const Transformation3D& transformation) const;

private:
	Color mColor;
	std::array<Vector3D, 8> mVertices;
};

}
