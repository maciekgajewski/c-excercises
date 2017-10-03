#include "surface3d.h"

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

void Surface3D::DrawLine(const Vector3D& a, const Vector3D& b, Color color)
{
	auto projectionA = GetProjection(a);
	auto projectionB = GetProjection(b);
	mSurface.DrawLine(projectionA, projectionB, color);
}

Pixel Surface3D::GetProjection(const Vector3D& vector) const
{
	const float scale = 3;
	
	int scaleX = mSurface.mSurface->w / scale;
	int scaleY = mSurface.mSurface->h / scale;
	int centerX = mSurface.mSurface->w / 2;
	int centerY = mSurface.mSurface->h / 2;

	return {
		centerX + static_cast<int>(vector.x / vector.z * scaleX),
				centerY - static_cast<int>(vector.y / vector.z * scaleY)
	};
}

}
