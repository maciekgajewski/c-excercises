#pragma once

#include "float3.h"
#include "material.h"

class IntersectionInfo
{
public:
    IntersectionInfo()
    {
        rayParam = 0;
        material = Material();
        normal = Float3();
    }
    IntersectionInfo(const float &t, const Float3 &n, const Material &material) : rayParam(t), normal(n), material(material)
    {

    }

    const Material& GetMaterial() const
    {
        return material;
    }

    const Float3 GetNormal() const
    {
        return normal;
    }

    float GetRayParam() const
    {
        return rayParam;
    }

    void SetRayParam(float v)
    {
        rayParam = v;
    }

private:
    //This is the parameter in the parametric equation of the ray
    float rayParam;
    Float3 normal;
    Material material;
};