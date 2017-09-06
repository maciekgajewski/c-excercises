#pragma once

#include <vector>
#include <memory>

#include "float3.h"
#include "ray.h"
#include "intersectioninfo.h"
#include "primitive.h"

class Scene
{
public:
    Scene();
    void AddPrimitive(Primitive* primitive);
    bool Intersect(const Ray& ray, IntersectionInfo &info);
    void SetLightPosition(const Float3& lightPosition);
    Float3 GetLightPosition() const
    {
        return lightPosition;
    }
private:
    Float3 lightPosition;
    std::vector<Primitive*> primitives;
};
