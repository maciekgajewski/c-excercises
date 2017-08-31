#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/float3.h>

#include <iostream>
#include <memory>

#include <displaylib/renderingengine.h>

#define IMAGE_SIZE 512

int main(int, char**)
{
	std::cout << "Hello" << std::endl;

    RenderingEngine r = RenderingEngine(IMAGE_SIZE);
    r.AddPrimitive(std::shared_ptr<Primitive>(new Sphere(Float3(-1e5 - 100, 0, -200), 1e5, Material(Float3(1, 0, 0), MaterialType::Diffuse))));
    r.AddPrimitive(std::shared_ptr<Primitive>(new Sphere(Float3(1e5 + 100, 0, -200), 1e5, Material(Float3(0, 0, 1), MaterialType::Diffuse))));
    r.AddPrimitive(std::shared_ptr<Primitive>(new Sphere(Float3(0, -1e5 - 100, -200), 1e5, Material(Float3(0, 1, 0), MaterialType::Diffuse))));
    r.AddPrimitive(std::shared_ptr<Primitive>(new Sphere(Float3(0, 1e5 + 100, -200), 1e5, Material(Float3(1, 1, 1), MaterialType::Diffuse))));
    r.AddPrimitive(std::shared_ptr<Primitive>(new Sphere(Float3(0, 0, -1e5 - 200), 1e5, Material(Float3(1, 1, 1), MaterialType::Diffuse))));
    r.AddPrimitive(std::shared_ptr<Primitive>(new Sphere(Float3(-15, -10, -50), 10, Material(Float3(0.5f, 1, 1), MaterialType::Specular))));
    r.AddPrimitive(std::shared_ptr<Primitive>(new Sphere(Float3(15, -10, -40), 10, Material(Float3(0.5f, 1, 1), MaterialType::Diffuse))));

    r.SetLightPosition(Float3(-5, 90, -25));
    const std::vector<Float3> image = r.Render();

    Display::Window win("Hello", 10, 10, IMAGE_SIZE, IMAGE_SIZE);
    Display::Surface surf(IMAGE_SIZE, IMAGE_SIZE);

    for(int i = 0; i < IMAGE_SIZE; i++)
    {
        for(int j = 0; j < IMAGE_SIZE; j++)
        {
            Float3 currentPixel = image[i * IMAGE_SIZE + j];
            surf.SetPixel(i, j, currentPixel.x * 255, currentPixel.y * 255, currentPixel.z * 255); // red pixel at 10x10
        }
    }

    win.Display(surf);
    Display::Delay(100000);

	Display::Delay(1000);

	return 0;
}
