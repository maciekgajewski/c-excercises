#include "sphere.h"

Sphere::Sphere(const Float3& o, const float& rad, const Material& material) : o(o), rad(rad), material(material)
{

}

IntersectionInfo Sphere::Intersect(const Ray &r)
{
    Float3 op = o - r.GetOrigin();
    float t, eps = 1e-4f, b = op.Dot(r.GetDirection()), det = b * b - op.Dot(op) + rad * rad;
    if(det < 0)
    {
        return IntersectionInfo();
    }
    else
    {
        det = sqrt(det);
    }
    t = (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
    return IntersectionInfo(t, ((r.GetOrigin() + r.GetDirection() * t) - o).Normalize(), material);
}
