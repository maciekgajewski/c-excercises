#include "cube.h"

namespace Display {

void Cube::Draw(Surface3D& surface)
{
	Vector2D edges[] = { Vector2D{ -1, -1 }, Vector2D{ -1, +1 }, Vector2D{ +1, -1 }, Vector2D{ +1, +1 } };

	for (auto i = 0; i < 4; ++i)
	{
		auto v = edges[i];
		surface.DrawLine(mTransformation * Vector3D{ v.x(), v.y(), -1 }, mTransformation * Vector3D{ v.x(), v.y(), +1 }, mColor);
		surface.DrawLine(mTransformation * Vector3D{ v.x(), -1, v.y() }, mTransformation * Vector3D{ v.x(), +1, v.y() }, mColor);
		surface.DrawLine(mTransformation * Vector3D{ -1, v.x(), v.y() }, mTransformation * Vector3D{ +1, v.x(), v.y() }, mColor);
	}
}

}