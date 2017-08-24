#include "cube.h"

namespace Display {

Cube::Cube(Vector3D c, float size)
{
	auto half = size * 0.5f;
	vertices[0] = {c.x - half, c.y - half, c.z - half};
	vertices[1] = {c.x + half, c.y - half, c.z - half};
	vertices[2] = {c.x - half, c.y + half, c.z - half};
	vertices[3] = {c.x + half, c.y + half, c.z - half};
	vertices[4] = {c.x - half, c.y - half, c.z + half};
	vertices[5] = {c.x + half, c.y - half, c.z + half};
	vertices[6] = {c.x - half, c.y + half, c.z + half};
	vertices[7] = {c.x + half, c.y + half, c.z + half};
}

}
