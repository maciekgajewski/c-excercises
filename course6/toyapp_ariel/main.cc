#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/float3.h>
#include <displaylib/renderingengine.h>
#include <displaylib/mat4.h>
#include <displaylib/triangle.h>

#include <chrono>

#define IMAGE_SIZE 512

using Time = std::chrono::time_point<std::chrono::system_clock>;
using Clock = std::chrono::system_clock;
using FDuration = std::chrono::duration<float>;

int main(int, char**)
{
    Display::Window win("Hello", 10, 10, IMAGE_SIZE, IMAGE_SIZE);
    Display::Surface surf(IMAGE_SIZE, IMAGE_SIZE);    

    Sphere* diffuseSphere (new Sphere(Float3(15, -10, -20), 10, Material(Float3(0.5f, 1, 1), MaterialType::Diffuse)));
    Sphere* reflectiveSphere (new Sphere(Float3(-15, -10, -70), 10, Material(Float3(), MaterialType::Specular)));

    Scene scene;
    scene.AddPrimitive(new Sphere(Float3(-1e5 - 100, 0, -200), 1e5, Material(Float3(1, 0, 0), MaterialType::Diffuse)));
    scene.AddPrimitive(new Sphere(Float3(1e5 + 100, 0, -200), 1e5, Material(Float3(0, 0, 1), MaterialType::Diffuse)));
    scene.AddPrimitive(new Sphere(Float3(0, -1e5 - 100, -200), 1e5, Material(Float3(0, 1, 0), MaterialType::Diffuse)));
    scene.AddPrimitive(new Sphere(Float3(0, 1e5 + 100, -200), 1e5, Material(Float3(1, 1, 1), MaterialType::Diffuse)));
    scene.AddPrimitive(new Sphere(Float3(0, 0, -1e5 - 200), 1e5, Material(Float3(1, 1, 1), MaterialType::Diffuse)));
    
    Float3 center(0, -30, -30);
    Float3 right(10, -30, -40);
    Float3 left(-10, -30, -40);
    Float3 top(0, -10, -40);

    scene.AddPrimitive(new Triangle(right, top, center, Material(Float3(), MaterialType::Specular)));
    scene.AddPrimitive(new Triangle(left, top, right, Material(Float3(), MaterialType::Specular)));
    scene.AddPrimitive(new Triangle(center, top, left, Material(Float3(0.75f, 0.25f, 0.25f), MaterialType::Diffuse)));

    scene.AddPrimitive(reflectiveSphere);
    scene.AddPrimitive(diffuseSphere);

    scene.SetLightPosition(Float3(-5, 90, -25));

    RenderingEngine r = RenderingEngine(IMAGE_SIZE, surf, scene);

    SDL_Event event;
    bool quit = 0;

    Float3 targetPosition1(15, -10, -30);
    float targetSize = 20.f;

    Time start, end;
    start = std::chrono::system_clock::now();

    while (!quit)
    {
        FDuration elapsed_seconds = Clock::now() - start;
        Float3 intermidiatePosition = Float3::Lerp(diffuseSphere->GetBaseOrigin(), targetPosition1, Float3::Clamp01(elapsed_seconds.count() / 5.0f));
        diffuseSphere->ApplyTranslation(intermidiatePosition - diffuseSphere->GetBaseOrigin());

        float intermediateSize = Float3::Lerp(reflectiveSphere->GetBaseRadius(), targetSize, Float3::Clamp01(elapsed_seconds.count() / 7.0f));
        reflectiveSphere->ApplyScale(intermediateSize / reflectiveSphere->GetBaseRadius());

        r.Render();

        win.Display(surf);
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
        }
    }

	return 0;
}
