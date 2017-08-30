#pragma once

#include <vector>
#include <memory>
#include <string>

#include "primitives.h"

namespace Draw {

using namespace Draw::Primitives;

class RenderObject {
public:
	RenderObject();
	void Add(Primitive* prim);
	std::string ToString();
	void Print();
	std::vector<std::unique_ptr<Primitive>>* GetData() {return &data;}

private:
	std::vector<std::unique_ptr<Primitive>> data;
};


}
