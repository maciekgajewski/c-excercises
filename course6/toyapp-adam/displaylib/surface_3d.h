#pragma once

#include "camera.h"
#include "color.h"
#include "math/matrix.h"
#include "math/triangle.h"
#include "math/vector.h"
#include "mesh.h"
#include "surface_2d.h"

namespace Display {

using Math::Triangle3D;
using Math::Vector2D;
using Math::Vector3D;

class Surface3D
{
public:
	Camera camera;

	Surface3D(Surface2D& surface2D);

	void Clear(Color color) { mSurface.Clear(color); }
	void SetPixel(Vector3D vector, Color color) { mSurface.SetPixel(Project(vector), color); }
	void DrawLine(Vector3D start, Vector3D end, Color color) { mSurface.DrawLine(Project(start), Project(end), color); }
	void DrawTriangle(const Triangle3D& triangle, Color color);
	void DrawMesh(const Mesh& mesh, const Matrix44& view);
private:
	Surface2D& mSurface;

	Vector3D Project(Vector3D vector) const;
	Triangle3D Project(Triangle3D triangle) const;
};

}
