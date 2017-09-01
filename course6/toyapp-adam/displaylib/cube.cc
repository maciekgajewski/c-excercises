#include "cube.h"

namespace Display {

Cube::Cube(Vector3D center, float size)
:	mCenter{center},
	mHalfSize{size * 0.5f}
{}

void Cube::Draw(Surface3D& surface, Color color) const
{
	auto& c = mCenter;
	auto& h = mHalfSize;

	Vector3D{c.x - h, c.y - h, c.z - h}.Draw(surface, color);
	Vector3D{c.x + h, c.y - h, c.z - h}.Draw(surface, color);
	Vector3D{c.x - h, c.y + h, c.z - h}.Draw(surface, color);
	Vector3D{c.x + h, c.y + h, c.z - h}.Draw(surface, color);
	Vector3D{c.x - h, c.y - h, c.z + h}.Draw(surface, color);
	Vector3D{c.x + h, c.y - h, c.z + h}.Draw(surface, color);
	Vector3D{c.x - h, c.y + h, c.z + h}.Draw(surface, color);
	Vector3D{c.x + h, c.y + h, c.z + h}.Draw(surface, color);
}

}
