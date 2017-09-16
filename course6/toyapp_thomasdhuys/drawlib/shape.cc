#include <iostream>

#include "shape.h"

namespace Draw {

//Shape::Shape(const Shape& shape) : name(shape.name)
//{
// std::unordered_set<Index>
//}

Shape::Shape(Shape&& shape) : name(std::move(shape.name)),
primitives(std::move(shape.primitives)), scale(std::move(shape.scale))
{
	
}

void Shape::AddPoint(Index idx0)
{
	primitives.emplace_back(new Point(idx0));
}

void Shape::AddLine(Index idx0, Index idx1)
{
	primitives.emplace_back(new Line(idx0, idx1));
}

void Shape::AddTriangle(Index idx0, Index idx1, Index idx2)
{
	primitives.emplace_back(new Triangle(idx0, idx1, idx2));
}

std::ostream& operator<<(std::ostream& s, const Shape& sh)
{
	return s << sh.name;
}

Shape ShapeFactory::GetSquarePoints()
{
	Shape shape("SquarePoints");
	auto indices = GetSquareIndices();

	for (Index& idx : indices){
		shape.AddPoint(idx);
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
