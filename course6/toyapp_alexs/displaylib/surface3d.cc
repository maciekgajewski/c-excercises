#include "surface.h"
#include "surface3d.h"
#include "color.h"
#include "vector2d.h"
#include "vector3d.h"

#include <cassert>

namespace Display {

Surface3D::Surface3D(Surface& surface) : mSurface(surface)
{
}

void Surface3D::Clear(Color color)
{
	mSurface.Clear(color);
}

void Surface3D::SetPixel(const Vector3D& vector, Color color)
{
	auto projection = GetProjection(vector);
	mSurface.SetPixel(projection, color);
}

Vector2D Surface3D::GetProjection(const Vector3D& vector) const
{
	const float scale = 3;
	
	int scaleX = mSurface.mSurface->w / scale;
	int scaleY = mSurface.mSurface->h / scale;
	int centerX = mSurface.mSurface->w / 2;
	int centerY = mSurface.mSurface->h / 2;

	return Vector2D {
		centerX + static_cast<int>(vector.x / vector.z * scaleX),
				centerY - static_cast<int>(vector.y / vector.z * scaleY)
	};
}

}
