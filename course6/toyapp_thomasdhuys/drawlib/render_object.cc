#include "render_object.h"

namespace Draw {
namespace Render {

RenderObject::RenderObject() {}

void RenderObject::Add(Primitive* prim)
{
	data.push_back(std::unique_ptr<Primitive>(prim));
}

}
}
