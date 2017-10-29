#include "scene.h"

Scene::Scene()
{

}

void Scene::AddPrimitive(Primitive* primitive)
{
    primitives.push_back(primitive);
}

bool Scene::Intersect(const Ray &ray, IntersectionInfo& info)
{
    info.SetRayParam(INFINITY);
    IntersectionInfo current;

    for(int i = 0; i < primitives.size(); i++)
    {
        if(primitives[i]->Intersect(ray, current) && current.GetRayParam() < info.GetRayParam())
        {
            info = current;
        }
    }

    return info.GetRayParam() < INFINITY;
}

void Scene::SetLightPosition(const Float3 &lightPosition)
{
    this->lightPosition = lightPosition;
}
