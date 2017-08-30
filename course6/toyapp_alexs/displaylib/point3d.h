#pragma once

#include <cstdint>

namespace Display {

struct Point3D {
    Point3D(int x, int y, int z);

    int x, y, z;
};

}
