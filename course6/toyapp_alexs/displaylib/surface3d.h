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
	void SetPixel(const Vector<double, 3>& vector, Color color);
	void DrawLine(const Vector<double, 3>& a, const Vector<double, 3>& b, Color color);

private:
	Vector<int, 2> GetProjection(const Vector<double, 3>& vector) const;

	friend class Window;

	Surface& mSurface;
};

}
