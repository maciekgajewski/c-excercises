#pragma once

#include "color.h"

namespace Display {

class Surface3D;


struct Vector2D
{
	float x = 0.0f;
	float y = 0.0f;
};

struct Vector3D
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	void Draw(Surface3D& surface, Color color) const;
};

}
