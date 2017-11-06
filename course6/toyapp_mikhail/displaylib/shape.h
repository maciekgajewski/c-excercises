#pragma once

#include "matrix.h"
#include "triangle.h"
#include "surface3d.h"
#include "rgb.h"

#include <vector>

namespace Display {

class Shape
{
private:
	Matrix mTransformation;
	RGB mColor;
	std::vector<Triangle> mSides;

public:
	Shape(Matrix m, RGB color, std::vector<Triangle> sides) :
		mTransformation(m),
		mColor(color),
		mSides(sides)
	{}

	Shape() = default;

	void SetColor(RGB color) { mColor = color; }

	void SetTransformation(Matrix m) { mTransformation = m; }

	void Draw(Surface3D& surface) { surface.Draw(mSides, mColor); }

	static Shape LoadFromFile(const std::string& filePath);
};

}