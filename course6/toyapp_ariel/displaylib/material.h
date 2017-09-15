#pragma once

#include "float3.h"

enum MaterialType
{
    Diffuse,
    Specular
};

class Material
{
public:    
    Material() : matType(MaterialType::Diffuse), color(Float3())
    {

    }

    Material(const Float3 &color, const MaterialType &matType) : color(color), matType(matType)
    {

    }

    Float3 GetColor() const
    {
        return color;
    }

    MaterialType GetMatType() const
    {
        return matType;
    }

private:
    Float3 color;
    MaterialType matType;
};
