#ifndef SPHERE_H
#define SPHERE_H

#include "float3.h"
#include "ray.h"
#include "primitive.h"
#include "material.h"

class Sphere : public Primitive
{
public:
    Sphere(const Float3& o, const float& rad, const Material& material);
    IntersectionInfo Intersect(const Ray& r);
private:
    Float3 o;
    float rad;
    Float3 c;
    Material material;
};

#endif // SPHERE_H
