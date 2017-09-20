#pragma once

#include "ray.h"
#include "intersectioninfo.h"

class Primitive
{
public:
    virtual bool Intersect(const Ray& ray, IntersectionInfo& intersectionInfo) const = 0;
    virtual void ApplyTranslation(const Float3& v) = 0;
    virtual void ApplyScale(float v) = 0;
};
