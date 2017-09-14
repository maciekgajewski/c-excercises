#pragma once

#include "float3.h"
#include "sphere.h"
#include "primitive.h"
#include "surface.h"
#include "scene.h"

#include <cmath>
#include <vector>
#include <memory>

class RenderingEngine
{
public:
    RenderingEngine(const int& imageSize, Display::Surface& surf, Scene& scene);
    const void Render();
    Float3 RayTrace(int depth, const Ray& ray);
private:
    Scene scene;
    Display::Surface& surf;
    int imageSize;

    Ray CreatePrimaryRay(int x, int y);
    Float3 GetDirectIllumination(const Float3& position, IntersectionInfo& info, const Float3& lightPostion, const Float3& lightIntensity);
};
