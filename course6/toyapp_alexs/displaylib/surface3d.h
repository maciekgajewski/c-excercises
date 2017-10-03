#pragma once

#include "surface.h"
#include "color.h"
#include "vector.h"

namespace Display {

class Surface3D 
{
public:
	Surface3D(Surface& surface);

	void Clear(Color color);
	void SetPixel(const Vector3D& vector, Color color);
	void DrawLine(const Vector3D& a, const Vector3D& b, Color color);

private:
	Pixel GetProjection(const Vector3D& vector) const;

	friend class Window;

	Surface& mSurface;
};

}
