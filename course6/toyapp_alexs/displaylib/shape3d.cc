#include "vector3d.h"
#include "shape3d.h"
#include "color.h"

namespace Display {

Shape3D::Shape3D(Vector3D position, Color color)
    : position(position), color(color)
{
}

}
