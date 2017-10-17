#include "surface3d.h"

namespace Display {

Vector2D Surface3D::Transform(Vector3D p)
{
	auto transformed = mCameraTransform * p;

	auto pushBack3dShift = Vector3D{ 0, 0, 3.5 };
	const auto scaling = 200.0;
	auto centerScreenShift = Vector2D{ mSurface.GetW() / 2.0, mSurface.GetH() / 2.0 };

	auto shifted3d = transformed + pushBack3dShift;
	auto zfactor = std::abs(shifted3d.z()) < 0.001 ? 0.001 : shifted3d.z();

	return centerScreenShift + Vector2D{ shifted3d.x(), shifted3d.y() } *(scaling / zfactor);
}

void Surface3D::Draw(const Triangle& t, RGB color)
{
	DrawLine(t[0], t[1], color);
	DrawLine(t[0], t[2], color);
	DrawLine(t[1], t[2], color);
}

void Surface3D::SetPixel(Vector3D p, RGB color)
{
	mSurface.SetPixel(Transform(p), color);
}

void Surface3D::DrawLine(const Vector3D& start, const Vector3D& end, RGB color)
{
	mSurface.DrawLine(Transform(start), Transform(end), color);
}

void Surface3D::Draw(const std::vector<Triangle>& tt, RGB color)
{
	for (auto t : tt)
	{
		Draw(t, color);
	}
}
}