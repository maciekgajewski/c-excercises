#pragma once
#include "types.h"
#include "vector3d.h"
#include "vector2d.h"

namespace Display {

void Delay(int msec);

Vector2D Render(Vector3D v);

Vector2D Rotate(Vector2D v, Vector2D origin, Degree angle);

}
