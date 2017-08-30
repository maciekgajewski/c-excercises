#pragma once

#include <vector>
#include <memory>

#include "primitives.h"

namespace Draw {
namespace Render {

using namespace Draw::Primitives;

class RenderObject {
public:
	RenderObject();
	void Add(Primitive* prim);
	std::vector<std::unique_ptr<Primitive>>* GetData();
private:
	std::vector<std::unique_ptr<Primitive>> data;
};


}
}
