#pragma once
#include <vector>
#include "primitives.h"
#include "render_object.h"

namespace Draw {

class Drawer {
public:
	static RenderObject Draw();

private:
	static std::vector<Index> GetSquareIndices();
	static RenderObject DrawSquarePoints();
};

}
