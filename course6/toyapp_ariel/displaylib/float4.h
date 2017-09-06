#pragma once

#include <cassert>

#include "float3.h"

class Float4
{
public:
    float x, y, z, w;

    Float4() : x(0), y(0), z(0), w(0)
    {

    }

    Float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
    {

    }

    Float4(float f) : x(f), y(f), z(f), w(f)
    {

    }

    Float4(const Float3& v) : x(v.x), y(v.y), z(v.z), w(1)
    {

    }

    Float3 GetXYZ ()
    {
        return {x, y, z};
    }
};
