#include "surface3d.h"

namespace Display {

Surface3D::Surface3D(Surface& surface) : mSurface(surface)
{
}

void Surface3D::Clear(Color color)
{
	mSurface.Clear(color);
}

void Surface3D::SetPixel(const Vector<double, 3>& vector, Color color)
{
	auto projection = GetProjection(vector);
	mSurface.SetPixel(projection, color);
}

void Surface3D::DrawLine(const Vector<double, 3>& a, const Vector<double, 3>& b, Color color)
{
	auto projectionA = GetProjection(a);
	auto projectionB = GetProjection(b);
	mSurface.DrawLine(projectionA, projectionB, color);
}

Vector<int, 2> Surface3D::GetProjection(const Vector<double, 3>& vector) const
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
