#include "renderingengine.h"

RenderingEngine::RenderingEngine(const int &imageSize) : imageSize(imageSize)
{
    image = std::vector<Float3>(imageSize * imageSize);
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

const std::vector<Float3> RenderingEngine::Render()
{
    for(int i = 0; i < imageSize; i++)
    {
        for(int j = 0; j < imageSize; j++)
        {
            Ray primaryRay = CreatePrimaryRay(i, j);
            image[i * imageSize + j] = RayTrace(3, primaryRay);
        }
    }

    return image;
}

Float3 RenderingEngine::RayTrace(int depth, const Ray &ray)
{
    if(depth < 0)
    {
        return Float3();
    }

    IntersectionInfo info;
    if(Intersect(ray, info))
    {
        if(info.GetMaterial().GetMatType() == MaterialType::Diffuse)
        {
            Float3 position = ray.GetOrigin() + ray.GetDirection() * info.GetT();
            return GetDirectIllumination(position, info, lightPosition, Float3(12000));
        }
        else
        {
            Float3 position = ray.GetOrigin() + ray.GetDirection() * info.GetT();
            Float3 normal = info.GetNormal();
            Float3 reflectionDirection = ray.GetDirection() - normal * 2 * normal.Dot(ray.GetDirection());\
            Ray reflectionRay = Ray(position + normal * 0.001f, reflectionDirection);
            return RayTrace(depth - 1, reflectionRay);
        }
    }
}

Float3 RenderingEngine::GetDirectIllumination(const Float3& position, IntersectionInfo& info, const Float3 &lightPostion, const Float3 &lightIntensity)
{
    Float3 l = lightPostion - position;
    float distL = l.Length();
    l = l / distL;

    Float3 localLighting = info.GetMaterial().GetColor() * Float3::Clamp(info.GetNormal().Dot(l)) * lightIntensity / (distL * distL);
    return (localLighting + info.GetMaterial().GetColor() * 0.08f).Clamp();
}

void RenderingEngine::SetLightPosition(const Float3 &lightPosition)
{
    this->lightPosition = lightPosition;
}

void RenderingEngine::AddPrimitive(std::shared_ptr<Primitive> primitive)
{
    primitives.push_back(primitive);
}

bool RenderingEngine::Intersect(const Ray &ray, IntersectionInfo& info)
{
    info.SetT(INFINITY);
    IntersectionInfo current;

    for(int i = 0; i < primitives.size(); i++)
    {
        current = primitives[i]->Intersect(ray);
        if(current.GetT() && current.GetT() < info.GetT())
        {
            info = current;
        }
    }

    return info.GetT() < INFINITY;
}
