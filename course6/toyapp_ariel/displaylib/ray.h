#pragma once

#include "float3.h"

class Ray
{
public:    
    Ray(const Float3 &origin, const Float3 &direction) : origin(origin), direction(direction)
    {

    }
    Float3 GetOrigin() const
    {
        return origin;
    }

    Float3 GetDirection() const
    {
        return direction;
    }
private:
    Float3 origin, direction;
};
