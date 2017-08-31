#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include <math.h>
#include <vector>
#include <memory>

#include "float3.h"
#include "sphere.h"
#include "primitive.h"

class RenderingEngine
{
public:
    RenderingEngine(const int& imageSize);
    void AddPrimitive(std::shared_ptr<Primitive> primitive);
    void SetLightPosition(const Float3& lightPosition);
    const std::vector<Float3> Render();
    Float3 RayTrace(int depth, const Ray& ray);
private:
    Float3 lightPosition;
    std::vector<Float3> image;
    std::vector<std::shared_ptr<Primitive>> primitives;
    int imageSize;

    Ray CreatePrimaryRay(int x, int y);
    bool Intersect(const Ray& ray, IntersectionInfo &info);
    Float3 GetDirectIllumination(const Float3& position, IntersectionInfo& info, const Float3& lightPostion, const Float3& lightIntensity);
};

#endif // RENDERINGENGINE_H
