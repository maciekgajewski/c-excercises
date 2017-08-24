#include "vector.h"

namespace Display {

Vector2D Vector3D::project() const
{
	return Vector2D {
		x / z,
		y / z
	};
}

}