#pragma once

#include "float3.h"
#include "ray.h"
#include "primitive.h"
#include "material.h"

constexpr float Epsilon = 1e-8; 

class Triangle : public Primitive
{
public:
    Triangle(const Float3& v0, const Float3& v1, const Float3& v2, const Material& material) : 
    v0(v0), 
    v1(v1), 
    v2(v2), 
    material (material)
    {
        Float3 v0v1 = v1 - v0; 
        Float3 v0v2 = v2 - v0; 
        normal = v0v1.Cross(v0v2).Normalize();
    }

    Triangle(const Triangle& triangle) :
    v0(triangle.v0), 
    v1(triangle.v1), 
    v2(triangle.v2), 
    material (triangle.material),
    normal(triangle.normal)
    {

    }

    void ApplyTranslation(const Float3& v){}

    void ApplyScale(float v){}

    bool Intersect(const Ray &r, IntersectionInfo& intersectionInfo) const
    {
        Float3 v0v1 = v1 - v0; 
        Float3 v0v2 = v2 - v0; 
        Float3 pvec = r.GetDirection().Cross(v0v2); 
        float det = v0v1.Dot(pvec); 
        if (fabs(det) < Epsilon) return false; 
        float invDet = 1 / det; 
     
        Float3 tvec = r.GetOrigin() - v0; 
        float u = tvec.Dot(pvec) * invDet; 
        if (u < 0 || u > 1) return false; 
     
        Float3 qvec = tvec.Cross(v0v1); 
        float v = r.GetDirection().Dot(qvec) * invDet; 
        if (v < 0 || u + v > 1) return false; 
     
        float t = v0v2.Dot(qvec) * invDet; 

        intersectionInfo = IntersectionInfo(t, normal, material);
     
        return t > 0; 
    }
private:
    Float3 v0, v1, v2, normal;
    Material material;
};