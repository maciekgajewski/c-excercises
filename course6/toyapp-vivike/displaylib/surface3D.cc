#include "surface3D.h"

namespace Display {

	void Surface3D::SetPixel(Vector3D p, Color color)
	{
		surface.SetPixel(Transform(p), color);
	}

	void Surface3D::DrawLine(const Vector3D& start, const Vector3D& end, Color color)
	{
		surface.DrawLine(Transform(start), Transform(end), color);
	}
}