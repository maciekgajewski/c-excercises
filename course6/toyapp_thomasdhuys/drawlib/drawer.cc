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

	for (auto& idx : indices){
		ro.Add(new Draw::Primitives::Point(idx));
	}
	ro.Print();
	return ro;
}

std::vector<Index> Drawer::GetSquareIndices()
{
	std::vector<Index> indices(8);

	for (XCoord x : {-1, 1}) {
		for (XCoord y : {-1, 1}) {
			for (XCoord z : {1, 2}) {
				indices.push_back(Draw::Index(x,y,z));
				std::cout << "GetSqureIndices push_back" << std::endl;
			}
		}
	}
	std::cout << "GetSqureIndices returns" << std::endl;
	return indices;
}

}
