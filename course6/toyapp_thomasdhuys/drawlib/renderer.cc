#include <iostream>

#include "renderer.h"
#include "matrix.h"

namespace Draw {

void Renderer::Render(Scenes& scenes)
{
	for (auto& scene : scenes) {
		std::cout << "scene: " << scene << std::endl;
		Render(scene);
		window.Display(surface);
		Display::Delay(5000*2);
	}
}

void Renderer::Render(Scene& scene)
{
	for (auto& shape : scene.GetShapes()) {
		Render(shape);
	}
}

void Renderer::Render(Shape& shape)
{
	for (auto& primitive : shape.GetPrimitives()){

		std::cout << *primitive << std::endl;

		if (dynamic_cast<Point*>(primitive.get()))
		{
			Render(dynamic_cast<Point&>(*primitive));
		}
		else if (dynamic_cast<Line*>(primitive.get()))
		{
			Render(dynamic_cast<Line&>(*primitive));
		}
		else
		{
			Render(dynamic_cast<Triangle&>(*primitive));
		}
	}
}

void Renderer::Render(Point& point)
{
	Vector3D v = point.idx0->vector;
	Color color = point.idx0->color;

    v = Matrix4x4::Scale(0.5) * v;
    v = Matrix4x4::Translation({0.0f,0.0f,3.0f}) * v;

	std::cout << "After transform: " << v << std::endl;

	VCoord x = v.x / v.z;
	VCoord y = v.y / v.z;

	Pixel halfDim;
	halfDim.x = surfaceWidth/2;
	halfDim.y = surfaceHeight/2;

	Pixel pixel;
	pixel.x = halfDim.x + x * halfDim.x;
	pixel.y = halfDim.y + y * halfDim.y;
	SetPixel(pixel, color);
}

void Renderer::Render(Line& line)
{
	Vector3D v1 = line.idx0->vector;
	Color color1 = line.idx0->color;

	Vector3D v2 = line.idx1->vector;
	Color color2 = line.idx1->color;

	Pixel pixel;
	pixel.x = v1.x;
	pixel.y = v2.y;
	SetPixel(pixel, color1);
}

void Renderer::Render(Triangle& triangle)
{

}

void Renderer::SetPixel(Pixel p, Color c)
{
	std::cout << "SetPixel(" << p.x << "," << p.y << "," << c << ")" << std::endl;
	surface.SetPixel(p.x, p.y, c.r, c.g, c.b);
}

Display::Window Renderer::DefaultWindow()
{
	return Display::Window("Hello", 10, 10, 800, 600);
}

Display::Surface Renderer::DefaultSurface()
{
	return Display::Surface(surfaceWidth,surfaceHeight);
}

Renderer::Renderer():
window(DefaultWindow()), surface(DefaultSurface()),
surfaceWidth(200), surfaceHeight(150) {}

}
