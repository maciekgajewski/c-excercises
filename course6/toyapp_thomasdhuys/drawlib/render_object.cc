#include <iostream>

#include "render_object.h"

namespace Draw {

RenderObject::RenderObject() {}

void RenderObject::Add(Primitive* prim)
{
	data.emplace_back(prim);
}

std::string RenderObject::ToString()
{
	std::string s = "RenderObject: (size:" + std::to_string(data.size()) + ")\n";
	for(auto& prim_ptr : data)
	{
		s = s + "\t" + prim_ptr->ToString() + "\n";
	}
	return s;
}

void RenderObject::Print()
{
	std::cout << ToString();
}
}
