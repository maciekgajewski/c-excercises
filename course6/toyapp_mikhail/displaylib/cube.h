#pragma once

#include "matrix.h"
#include "vector_common.h"
#include "surface3d.h"
#include "rgb.h"

namespace Display {

class Cube
{
private:
	Matrix mTransformation;
	RGB mColor;

public:
	Cube(Matrix m, RGB color) :mTransformation(m), mColor(color) {};
	void Draw(Surface3D& surface);
};

};