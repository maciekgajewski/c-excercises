#pragma once

#include "surface.h"
#include "matrix.h"
#include "vector_common.h"
#include "triangle.h"
#include "surface.h"

#include <vector>

namespace Display {

class Surface3D
{
private:
	Surface& mSurface;
	Matrix mCameraTransform;

	Vector2D Transform(Vector3D p);

public:
	Surface3D(Surface& s) : mSurface(s) {}

	void SetPixel(Vector3D p, RGB color);

	void DrawLine(const Vector3D& start, const Vector3D& end, RGB color);

	void Draw(const Triangle& t, RGB color);

	void Draw(const std::vector<Triangle>& tt, RGB color);
};

};