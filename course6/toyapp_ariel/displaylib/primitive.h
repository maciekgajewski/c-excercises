#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "ray.h"
#include "intersectioninfo.h"

class Primitive
{
public:
    virtual IntersectionInfo Intersect(const Ray& ray) = 0;
};

#endif // PRIMITIVE_H
