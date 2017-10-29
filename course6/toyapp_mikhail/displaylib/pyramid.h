#pragma once

#include "matrix.h"
#include "triangle.h"
#include "surface3d.h"
#include "rgb.h"

#include <vector>

namespace Display {

class Pyramid
{
private:
	Matrix mTransformation;
	RGB mColor;
	std::vector<Triangle> mSides;

public:
	Pyramid(Matrix m, RGB color);

	void Draw(Surface3D& surface) { surface.Draw(mSides, mColor); }
};

};