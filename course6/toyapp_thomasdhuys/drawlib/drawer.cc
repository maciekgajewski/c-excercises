#include "drawer.h"

namespace Draw {

RenderObject Drawer::Draw()
{
	auto ro = DrawSquarePoints();
	ro.Print();
	return ro;
}

RenderObject Drawer::DrawSquarePoints()
{
	RenderObject ro;
	auto indices = GetSquareIndices();

	for (Index& idx : indices){
		ro.Add(new Draw::Primitives::Point(idx));
	}
	ro.Print();
	return ro;
}

std::vector<Index> Drawer::GetSquareIndices()
{
	std::vector<Index> indices;
	indices.reserve(8);

	for (VCoord x : {-1, 1}) {
		for (VCoord y : {-1, 1}) {
			for (VCoord z : {1, 2}) {
				indices.push_back(std::make_shared<Vertex>(x,y,z));
				std::cout << "GetSqureIndices push_back: " << indices.back()->ToString()<< std::endl;
			}
		}
	}
	std::cout << "GetSqureIndices returns" << std::endl;
	return indices;
}

}
