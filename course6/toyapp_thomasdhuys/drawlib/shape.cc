#include <iostream>

#include "shape.h"

namespace Draw {

void Shape::Shape(Shape& shape)
{

}
void Shape::AddPoint(Index idx0)
{
	primitives.push_back(new Primitives::Point(idx0));
}

void Shape::AddLine(Index idx0; Index idx1)
{
	primitives.push_back(new Primitives::Line(idx0, idx1));
}

void Shape::AddTriangle(Index idx0, Index idx1, Index idx2)
{
	primitives.push_back(new Primitives::Triangle(idx0, idx1, idx2));
}

Shape ShapeFactory::GetSquarePoints()
{
	Shape shape("SquarePoints");
	auto indices = GetSquareIndices();

	for (Index& idx : indices){
		Shape.AddPoint(idx);
	}
	std::cout << shape << std::endl;
	return shape;
}

Shape ShapeFactory::GetSquareLines()
{
	Shape shape("SquareLines");
	auto indices = GetSquareIndices();
	return shape;
}

Shape ShapeFactory::GetSquareTriangles()
{
	Shape shape("SquareTriangles");
	auto indices = GetSquareIndices();
	return shape;
}

std::vector<Index> ShapeFactory::GetSquareIndices()
{
	std::vector<Index> indices;
	indices.reserve(8);

	for (VCoord x : {-1, 1}) {
		for (VCoord y : {-1, 1}) {
			for (VCoord z : {1, 2}) {
				indices.push_back(std::make_shared<Vertex>(x,y,z));
				std::cout << "GetSquareIndices push_back: " << *indices.back() << std::endl;
			}
		}
	}
	std::cout << "GetSqureIndices returns" << std::endl;
	return indices;
}

}
