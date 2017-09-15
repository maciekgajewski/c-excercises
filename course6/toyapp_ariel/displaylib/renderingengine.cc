#include "renderingengine.h"

#include <cassert>

RenderingEngine::RenderingEngine(const int &imageSize, Display::Surface& surf, Scene &scene) : imageSize(imageSize), surf(surf), scene(scene)
{
    assert(imageSize > 0);
}

Ray RenderingEngine::CreatePrimaryRay(int x, int y)
{
    int fov = 90;
    float Px = (2 * ((x + 0.5) / imageSize) - 1) * std::tan(fov / 2 * M_PI / 180);
    float Py = (1 - 2 * ((y + 0.5) / imageSize) * std::tan(fov / 2 * M_PI / 180));
    Float3 rayOrigin(0, 0, 0);
    Float3 rayDirection = Float3(Px, Py, -1).Normalize();

    return Ray(rayOrigin, rayDirection);
}

const void RenderingEngine::Render()
{
    surf.Clear(0, 0, 0);

    for(int i = 0; i < imageSize; i++)
    {
        for(int j = 0; j < imageSize; j++)
        {
            Ray primaryRay = CreatePrimaryRay(i, j);
            Float3 currentPixel = RayTrace(10, primaryRay);
            surf.SetPixel(i, j, currentPixel.x * 255, currentPixel.y * 255, currentPixel.z * 255); // red pixel at 10x10
        }
    }
}

Float3 RenderingEngine::RayTrace(int depth, const Ray &ray)
{
    if(depth < 0)
    {
        return Float3();
    }

    IntersectionInfo info;
    if(scene.Intersect(ray, info))
    {
        if(info.GetMaterial().GetMatType() == MaterialType::Diffuse)
        {
            Float3 position = ray.GetOrigin() + ray.GetDirection() * info.GetRayParam();
            return GetDirectIllumination(position, info, scene.GetLightPosition(), Float3(12000));
        }
        else
        {
            Float3 position = ray.GetOrigin() + ray.GetDirection() * info.GetRayParam();
            Float3 normal = info.GetNormal();
            Float3 reflectionDirection = ray.GetDirection() - normal * 2 * normal.Dot(ray.GetDirection());
            Ray reflectionRay = Ray(position + normal * 0.001f, reflectionDirection.Normalize());
            return RayTrace(depth - 1, reflectionRay);
        }
    }
}

Float3 RenderingEngine::GetDirectIllumination(const Float3& position, IntersectionInfo& info, const Float3 &lightPostion, const Float3 &lightIntensity)
{
    Float3 l = lightPostion - position;
    float distL = l.Length();
    l = l / distL;

    Float3 localLighting = info.GetMaterial().GetColor() * Float3::Clamp01(info.GetNormal().Dot(l)) * lightIntensity / (distL * distL);
    return (localLighting + info.GetMaterial().GetColor() * 0.08f).Clamp01();
}
