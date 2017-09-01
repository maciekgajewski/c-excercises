#include "vector.h"

#include "surface.h"

namespace Display {

void Vector3D::Draw(Surface3D& surface, Color color) const
{
	surface.SetPixel(*this, color);
}

}
