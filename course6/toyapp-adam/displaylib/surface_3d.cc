#include "surface_3d.h"

namespace Display {

using Math::Vector4D;

Surface3D::Surface3D(Surface2D& surface2D)
:	mSurface(surface2D)
{
	auto dimensions = surface2D.GetDimensions();
	camera.SetAspectRatio(dimensions.x / static_cast<float>(dimensions.y));
}

void Surface3D::DrawTriangle(const Triangle3D& triangle, Color color)
{
	mSurface.DrawTriangle(Triangle2D{Project(triangle[0]), Project(triangle[1]), Project(triangle[2])}, color);
}

Vector2D Surface3D::Project(Vector3D vector) const
{
	auto clipSpace = camera.GetProjectionMatrix() * Vector4D(vector);
	return {-clipSpace.x / clipSpace.w, clipSpace.y / clipSpace.w};
}

}
