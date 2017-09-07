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
	std::vector<std::unique_ptr<Primitive>>* GetData() {return &data;}
	friend std::ostream& operator<<(std::ostream& s , const RenderObject& ro);

private:
	std::vector<std::unique_ptr<Primitive>> data;
};

std::ostream& operator<<(std::ostream& s , const RenderObject& ro);
}
