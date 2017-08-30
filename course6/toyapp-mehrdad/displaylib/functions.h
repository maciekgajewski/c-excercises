#pragma once
#include "types.h"

namespace Display {

void Delay(int msec);

Vector2D Render(Vector3D v);

Vector2D Rotate(Vector2D v, Vector2D origin, Degree angle);

}
