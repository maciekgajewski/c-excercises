#pragma once

#include "surface.h"
#include "color.h"
#include "vector2d.h"
#include "vector3d.h"

namespace Display {

class Surface3D 
{
public:
	Surface3D(Surface& surface);

	void Clear(Color color);
	// TODO ask where it is better to use references and where copy ???
	void SetPixel(const Vector3D& vector, Color color);

private:
	Vector2D GetProjection(const Vector3D& vector) const;

	friend class Window;

	Surface& mSurface;
};

}
