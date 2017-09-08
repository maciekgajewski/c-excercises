#include "cube.h"

#include "math/matrix.h"
#include "surface_3d.h"

namespace Display {

Cube::Cube(Vector3D center, float size, Color fillColor, Color edgeColor)
:	mFillColor(fillColor),
	mEdgeColor(edgeColor)
{
	transform.SetPosition(center);
	transform.SetScale(size);
}

void Cube::Draw(Surface3D& surface, const Matrix44& view) const
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

	surface.DrawTriangle({v[0], v[1], v[2]}, mFillColor); // front
	surface.DrawTriangle({v[1], v[3], v[2]}, mFillColor); // front
	surface.DrawTriangle({v[5], v[4], v[6]}, mFillColor); // back
	surface.DrawTriangle({v[5], v[6], v[7]}, mFillColor); // back
	surface.DrawTriangle({v[0], v[4], v[5]}, mFillColor); // top
	surface.DrawTriangle({v[0], v[5], v[1]}, mFillColor); // top
	surface.DrawTriangle({v[2], v[7], v[6]}, mFillColor); // bottom
	surface.DrawTriangle({v[2], v[3], v[7]}, mFillColor); // bottom
	surface.DrawTriangle({v[0], v[2], v[4]}, mFillColor); // left
	surface.DrawTriangle({v[2], v[6], v[4]}, mFillColor); // left
	surface.DrawTriangle({v[1], v[5], v[3]}, mFillColor); // right
	surface.DrawTriangle({v[5], v[7], v[3]}, mFillColor); // right

	surface.DrawLine(v[0], v[1], mEdgeColor);
	surface.DrawLine(v[0], v[2], mEdgeColor);
	surface.DrawLine(v[0], v[4], mEdgeColor);
	surface.DrawLine(v[1], v[3], mEdgeColor);
	surface.DrawLine(v[1], v[5], mEdgeColor);
	surface.DrawLine(v[2], v[3], mEdgeColor);
	surface.DrawLine(v[2], v[6], mEdgeColor);
	surface.DrawLine(v[3], v[7], mEdgeColor);
	surface.DrawLine(v[4], v[5], mEdgeColor);
	surface.DrawLine(v[4], v[6], mEdgeColor);
	surface.DrawLine(v[5], v[7], mEdgeColor);
	surface.DrawLine(v[6], v[7], mEdgeColor);
}

}
