#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "primitives.h"

namespace Draw {

using ShapePrimitives = std::vector<Primitive>;

class Shape {
public:
	Shape(std::string name): name(name) {}
	Shape(const Shape& shape) = delete;
	Shape(Shape&& shape);

	void AddPoint(Index idx0);
	void AddLine(Index idx0, Index idx1);
	void AddTriangle(Index idx0, Index idx1, Index idx2);

	ShapePrimitives& GetPrimitives() {return primitives;}

private:
	ShapePrimitives primitives;
	int scale;
	std::string name;

	friend std::ostream& operator<<(std::ostream& s, const Shape& sh);
};

std::ostream& operator<<(std::ostream& s, const Shape& sh);

class ShapeFactory {
public:
	static Shape GetSquarePoints();
	static Shape GetSquareLines();
	static Shape GetSquareTriangles();
private:
	static std::vector<Index> GetSquareIndices();
};

}
