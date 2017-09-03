#include "cube.h"

#include "matrix.h"
#include "surface.h"

namespace Display {

Cube::Cube(Vector3D center, float size, Color color)
:	mColor(color)
{
	transform.SetPosition(center);
	transform.SetScale(size);
}

void Cube::Draw(Surface3D& surface, Matrix44& view) const
{
	auto modelView = view * transform.CreateMatrix();

	Vector3D v[] = {
		modelView * Vector3D{-1.0f, -1.0f, -1.0f},
		modelView * Vector3D{+1.0f, -1.0f, -1.0f},
		modelView * Vector3D{-1.0f, +1.0f, -1.0f},
		modelView * Vector3D{+1.0f, +1.0f, -1.0f},
		modelView * Vector3D{-1.0f, -1.0f, +1.0f},
		modelView * Vector3D{+1.0f, -1.0f, +1.0f},
		modelView * Vector3D{-1.0f, +1.0f, +1.0f},
		modelView * Vector3D{+1.0f, +1.0f, +1.0f}
	};

	surface.DrawLine(v[0], v[1], mColor);
	surface.DrawLine(v[0], v[2], mColor);
	surface.DrawLine(v[0], v[4], mColor);
	surface.DrawLine(v[1], v[3], mColor);
	surface.DrawLine(v[1], v[5], mColor);
	surface.DrawLine(v[2], v[3], mColor);
	surface.DrawLine(v[2], v[6], mColor);
	surface.DrawLine(v[3], v[7], mColor);
	surface.DrawLine(v[4], v[5], mColor);
	surface.DrawLine(v[4], v[6], mColor);
	surface.DrawLine(v[5], v[7], mColor);
	surface.DrawLine(v[6], v[7], mColor);
}

}
