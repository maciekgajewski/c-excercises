#include "vector3d.h"
#include "transformation3d.h"

namespace Display {

Move3D::Move3D(Vector3D move) : Transformation3D()
{
    mMove = move;
}

Vector3D Move3D::Apply(Vector3D vertex) const
{
    return {
        vertex.x + mMove.x,
        vertex.y + mMove.y,
        vertex.z + mMove.z,
    };
}

Scale3D::Scale3D(Vector3D scale) : Transformation3D()
{
    mScale = scale;
}

Vector3D Scale3D::Apply(Vector3D vertex) const
{
    return {
        vertex.x * mScale.x,
        vertex.y * mScale.y,
        vertex.z * mScale.z,
    };
}

}