#include <iostream>

#include "shape.h"

namespace Draw {

Shape::Shape(const Shape& shape) : name(shape.name), scale(shape.scale)
{
 //TODO: Implement such that Vertices in new shape are shared as well
 //use std::unordered_set<Vertex> to check which Vertices are already created
 //TODO: step2:

}

Shape::Shape(Shape&& shape) : name(std::move(shape.name)),
primitives(std::move(shape.primitives)), scale(std::move(shape.scale))
{

}

void Shape::AddPoint(Vertex idx0)
{
	primitives.push_back(std::make_unique<Point>(idx0));
}

void Shape::AddLine(Vertex idx0, Vertex idx1)
{
	primitives.push_back(std::make_unique<Line>(idx0, idx1));
}

void Shape::AddTriangle(Vertex idx0, Vertex idx1, Vertex idx2)
{
	primitives.push_back(std::make_unique<Triangle>(idx0, idx1, idx2));
}

std::ostream& operator<<(std::ostream& s, const Shape& sh)
{
	return s << sh.name;
}

Shape ShapeFactory::GetSquarePoints()
{
	Shape shape("SquarePoints");
	auto indices = GetSquareIndices();

	for (Vertex& idx : indices){
		shape.AddPoint(idx);
	}
	return shape;
}

Shape ShapeFactory::GetSquareLines()
{
	Shape shape("SquareLines");
	auto indices = GetSquareIndices();

	for (int j=0; j<4; ++j) {
		// Two circles
		for (int i : {0, 4}) {
			shape.AddLine(indices[j%4+i], indices[(j+1)%4+i]);
		}
		// Connecting the circles
		shape.AddLine(indices[j], indices[j+4]);
	}
	return shape;
}

Shape ShapeFactory::GetSquareTriangles()
{
	Shape shape("SquareTriangles");
	auto indices = GetSquareIndices();
	return shape;
}

std::vector<Vertex> ShapeFactory::GetSquareIndices()
{
	std::vector<Vertex> vertices;
	vertices.reserve(8);

	for (VCoord x : {-1, 1}) {
		for (VCoord y : {-1, 1}) {
			for (VCoord z : {-1, 1}) {
				vertices.emplace_back(x,y,z);
			}
		}
	}
	return vertices;
}

}
