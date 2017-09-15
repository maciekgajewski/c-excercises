#pragma once

#include "float3.h"
#include "ray.h"
#include "primitive.h"
#include "material.h"
#include "mat4.h"

class Sphere : public Primitive
{
public:
    Sphere(const Float3& o, const float& rad, const Material& material) :
        origin(o),
        baseOrigin(o),
        radius(rad),
        baseRadius(radius),
        material(material)
    {

    }

    bool Intersect(const Ray &r, IntersectionInfo& intersectionInfo) const
    {
        Float3 op = origin - r.GetOrigin();
        float rayParam, eps = 1e-4f, b = op.Dot(r.GetDirection()), det = b * b - op.Dot(op) + radius * radius;
        if(det < 0)
        {
            return false;
        }
        else
        {
            det = std::sqrt(det);
        }
        rayParam = (rayParam = b - det) > eps ? rayParam : ((rayParam = b + det) > eps ? rayParam : 0);
        intersectionInfo = IntersectionInfo(rayParam, ((r.GetOrigin() + r.GetDirection() * rayParam) - origin).Normalize(), material);
        return rayParam > 0;
    }

    void ApplyTranslation(const Float3 &v)
    {
        auto translationMatrix = Mat4::CreateTranslationMatrix(v);
        origin = (translationMatrix * Float4(baseOrigin.x, baseOrigin.y, baseOrigin.z, 1)).GetXYZ();
    }

    void ApplyScale(float v)
    {
        radius = baseRadius * v;
    }

    const Float3& GetBaseOrigin() const
    {
        return baseOrigin;
    }

    const Float3& GetOrigin() const
    {
        return origin;
    }

    float GetRadius() const
    {
        return radius;
    }

    float GetBaseRadius() const
    {
        return baseRadius;
    }
private:
    Float3 origin;
    const Float3 baseOrigin;

    float radius;
    float baseRadius;

    Material material;
};
