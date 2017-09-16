#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "primitives.h"



namespace Draw {
using namespace Draw::Primitives;
using ShapePrimitives = std::vector<Primitive>;

class Shape {
public:
	ShapePrimitives& GetPrimitives() {return primitives;}
	Shape(std::string name): name(name) {}
	Shape(Shape& shape);
	void AddPoint(Index idx0);
	void AddLine(Index idx0, Index idx1);
	void AddTriangle(Index idx0, Index idx1, Index idx2);

private:
	ShapePrimitives primitives;
	int scale;
	std::string name;
	friend std::ostream& operator<<(std::ostream& s, const Shape& sh);
};

std::ostream& operator<<(std::ostream& s, const Shape& sh) {return s << sh.name;}

class ShapeFactory {
public:
	static Shape GetSquarePoints();
	static Shape GetSquareLines();
	static Shape GetSquareTriangles();
private:
	static std::vector<Index> GetSquareIndices();
};

}
