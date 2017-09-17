#include "surface.h"
#include "cube.h"
#include "vector3d.h"

namespace Display {

Cube::Cube(Color color)
{
    mColor = color;
    mVertices[0] = {1, 1, 1};
    mVertices[1] = {1, 1, -1};
    mVertices[2] = {1, -1, 1};
    mVertices[3] = {-1, 1, 1};
    mVertices[4] = {1, -1, -1};
    mVertices[5] = {-1, 1, -1};
    mVertices[6] = {-1, -1, 1};
    mVertices[7] = {-1, -1, -1};
}

Cube& Cube::Move(Vector3D move)
{
    for (int i = 0; i < mVertices.size(); i++)
    {
        auto current = mVertices[i];
        mVertices[i] = {
            current.x + move.x,
            current.y + move.y,
            current.z + move.z
        };
    }
    return *this;
}

Cube& Cube::Scale(Vector3D scale)
{
    for (int i = 0; i < mVertices.size(); i++)
    {
        auto current = mVertices[i];
        mVertices[i] = {
            current.x * scale.x,
            current.y * scale.y,
            current.z * scale.z
        };
    }
    return *this;
}

void Cube::Draw(Surface3D& surface)
{
    surface.SetPixel(mVertices[0], this->mColor);
    surface.SetPixel(mVertices[1], this->mColor);
    surface.SetPixel(mVertices[2], this->mColor);
    surface.SetPixel(mVertices[3], this->mColor);
    surface.SetPixel(mVertices[4], this->mColor);
    surface.SetPixel(mVertices[5], this->mColor);
    surface.SetPixel(mVertices[6], this->mColor);
    surface.SetPixel(mVertices[7], this->mColor);
}

}
