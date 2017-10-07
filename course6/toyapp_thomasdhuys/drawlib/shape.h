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
	Shape(const Shape& shape);
	Shape(Shape&& shape);

	void AddPoint(Vertex idx0);
	void AddLine(Vertex idx0, Vertex idx1);
	void AddTriangle(Vertex idx0, Vertex idx1, Vertex idx2);

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
	static std::vector<Vertex> GetSquareIndices();
};

}
