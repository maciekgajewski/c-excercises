#pragma

#include "surface.h"
#include "vector3d.h"
#include <array>

namespace Display {

struct Cube
{
	Cube();

	void Draw(Surface& surface, Color color) const;

	std::array<Vector3D, 8> mVertices;
};

}
