#pragma once

#include <cstdint>

namespace Display {

struct Vector3D {
    Vector3D(int x, int y, int z);

    int x, y, z;
};

}
