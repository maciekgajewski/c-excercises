#ifndef INTERSECTIONINFO_H
#define INTERSECTIONINFO_H

#include "float3.h"
#include "material.h"

class IntersectionInfo
{
public:
    IntersectionInfo(){t = 0;}
    IntersectionInfo(const float& t, const Float3& n, const Material& material);
    Material& GetMaterial(){return material;}
    Float3 GetNormal() {return n;}
    float GetT() {return t;}
    void SetT(float v){ t = v;}
private:
    float t;
    Float3 n;
    Material material;
};

#endif // INTERSECTIONINFO_H
