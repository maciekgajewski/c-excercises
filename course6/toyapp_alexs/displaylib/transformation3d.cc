#include <cmath>

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

Rotate3D::Rotate3D(double thetaX, double thetaY, double thetaZ)
{
    mThetaX = thetaX;
    mThetaY = thetaY;
    mThetaZ = thetaZ;
}

Vector3D Rotate3D::Apply(Vector3D vertex) const
{
    return ApplyZ(ApplyY(ApplyX(vertex)));
}

Vector3D Rotate3D::ApplyX(Vector3D vertex) const
{
    return {
        vertex.x,
        cos(mThetaX) * vertex.y - sin(mThetaX) * vertex.z,
        sin(mThetaX) * vertex.y + cos(mThetaX) * vertex.z,
    };
}

Vector3D Rotate3D::ApplyY(Vector3D vertex) const
{
    return {
        cos(mThetaY) * vertex.x + sin(mThetaY) * vertex.z,
        vertex.y,
        - sin(mThetaY) * vertex.x + cos(mThetaY) * vertex.z,
    };
}

Vector3D Rotate3D::ApplyZ(Vector3D vertex) const
{
    return {
        cos(mThetaZ) * vertex.x - sin(mThetaZ) * vertex.y,
        sin(mThetaZ) * vertex.x + cos(mThetaZ) * vertex.y,
        vertex.z,
    };
}

}