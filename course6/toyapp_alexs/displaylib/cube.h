#pragma once

#include "vector2d.h"
#include "shape3d.h"
#include "surface3d.h"
#include "color.h"

namespace Display {

class Cube: public Shape3D {
public:
    Cube(Vector3D position, Color color, float size);
    void Draw(Surface3D& surface);

private:
    float size;
};

}
