#pragma once

#include "vector3d.h"
#include "surface.h"

namespace Display {

class Shape3D {
public:
    Shape3D(Vector3D position, Color color);
    virtual void Draw(Surface& surface) {};
    virtual ~Shape3D() = default;

protected:
    Vector3D position;
    Color color;
};

}
