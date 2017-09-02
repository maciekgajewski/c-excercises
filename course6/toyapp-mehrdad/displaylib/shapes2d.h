#pragma

#include "surface.h"
#include "vector2d.h"
#include <array>

namespace Display {

struct Rect
{
	Rect(Vector2D topLeft, Size size);

	void Draw(Surface& surface, Color color);
	void Rotate(Degree rotationAngle);

	std::array<Vector2D, 4> mVertices;
};

}
