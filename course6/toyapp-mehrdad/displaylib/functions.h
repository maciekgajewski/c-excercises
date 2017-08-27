#pragma once
#include "types.h"

namespace Display {

void Delay(int msec);

Vector2D Render(Vector3D v);

Vector2D Rotate(Vector2D v, Vector2D origin, Degree angle);

Polygon Rotate(Polygon p, Vector2D origin, Degree angle);

Polygon ToPolygon(Rect rect);

Vector2D GetCenter(Rect rect);
}
