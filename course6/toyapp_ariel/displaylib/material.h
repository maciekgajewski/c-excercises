#ifndef MATERIAL_H
#define MATERIAL_H

#include "float3.h"

enum MaterialType
{
    Diffuse,
    Specular
};

class Material
{
public:    
    Material(){}
    Material(const Float3& color, const MaterialType& matType);
    Float3 GetColor() const {return color;}
    MaterialType GetMatType(){return matType;}
private:
    Float3 color;
    MaterialType matType;
};

#endif // MATERIAL_H
