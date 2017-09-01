#include "cube.h"

#include "matrix.h"
#include "surface.h"

namespace Display {

Cube::Cube(Vector3D center, float size)
:	mCenter{center},
	mHalfSize{size * 0.5f}
{}

void Cube::Draw(Surface3D& surface, Matrix44& view, Color color) const
{
	auto c = mCenter;
	auto h = mHalfSize;

	auto model = transform.CreateMatrix();
	auto modelView = model * view;

	Vector3D v[] = {
		modelView * Vector3D{c.x - h, c.y - h, c.z - h},
		modelView * Vector3D{c.x + h, c.y - h, c.z - h},
		modelView * Vector3D{c.x - h, c.y + h, c.z - h},
		modelView * Vector3D{c.x + h, c.y + h, c.z - h},
		modelView * Vector3D{c.x - h, c.y - h, c.z + h},
		modelView * Vector3D{c.x + h, c.y - h, c.z + h},
		modelView * Vector3D{c.x - h, c.y + h, c.z + h},
		modelView * Vector3D{c.x + h, c.y + h, c.z + h}
	};

	surface.DrawLine(v[0], v[1], color);
	surface.DrawLine(v[0], v[2], color);
	surface.DrawLine(v[0], v[4], color);
	surface.DrawLine(v[1], v[3], color);
	surface.DrawLine(v[1], v[5], color);
	surface.DrawLine(v[2], v[3], color);
	surface.DrawLine(v[2], v[6], color);
	surface.DrawLine(v[3], v[7], color);
	surface.DrawLine(v[4], v[5], color);
	surface.DrawLine(v[4], v[6], color);
	surface.DrawLine(v[5], v[7], color);
	surface.DrawLine(v[6], v[7], color);
}

}
