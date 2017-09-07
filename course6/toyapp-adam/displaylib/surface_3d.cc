#include "surface_3d.h"

namespace Display {

using Math::Vector4D;

Surface3D::Surface3D(Surface2D& surface2D)
:	mSurface(surface2D)
{
	camera.SetScreenSize(surface2D.GetDimensions());
}

Vector2D Surface3D::Project(Vector3D vector) const
{
	auto clipSpace = camera.GetProjectionMatrix() * Vector4D(vector);
	return {-clipSpace.x / clipSpace.w, clipSpace.y / clipSpace.w};
}

}
