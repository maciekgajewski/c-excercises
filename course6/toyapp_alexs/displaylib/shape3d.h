#pragma once

#include "vector3d.h"
#include "surface3d.h"

namespace Display {

class Shape3D {
public:
    Shape3D(Vector3D position, Color color);
    virtual void Draw(Surface3D& surface) = 0;
    virtual ~Shape3D() = default;

protected:
    Vector3D position;
    Color color;
};

}
