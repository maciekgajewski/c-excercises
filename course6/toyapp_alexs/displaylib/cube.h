#pragma once

#include <array>

#include "vector2d.h"
#include "surface3d.h"
#include "color.h"

namespace Display {

class Cube {
public:
    Cube(Color color);
    void Draw(Surface3D& surface);
    Cube& Move(Vector3D move);
    Cube& Scale(Vector3D scale);

private:
    Color mColor;
    std::array<Vector3D, 8> mVertices;
};

}
