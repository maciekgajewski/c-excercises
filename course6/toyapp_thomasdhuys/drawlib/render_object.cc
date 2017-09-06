#include <iostream>

#include "render_object.h"

namespace Draw {

RenderObject::RenderObject() {}

void RenderObject::Add(Primitive* prim)
{
	data.emplace_back(prim);
}

std::ostream& operator<<(std::ostream& s , const RenderObject& ro)
{
	s << "RenderObject: (size:" << ro.data.size() << ")\n";
	for(auto& prim_ptr : ro.data)
	{
		s << "\t" << *prim_ptr << "\n";
	}
	return s;
}

}
