#pragma

#include "surface.h"
#include "types.h"
#include <array>

namespace Display {

struct Rect
{
	Rect(Vector2D topLeft, Size size);

	void Draw(Surface& surface, Color color);
	void Rotate(Degree rotationAngle);

	std::array<Vector2D, 4> mVertices;
};

struct Cube
{
	Cube();

	void Draw(Surface& surface, Color color) const;

	std::array<Vector3D, 8> mVertices;
};

}
