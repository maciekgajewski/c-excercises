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
		Display::Delay(5000);
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
	Vector3D v = point.vtx0.vector;
	Color color = point.vtx0.color;

    v = Matrix4x4::Scale(0.5) * v;
    v = Matrix4x4::Translation({0.0f,0.0f,3.0f}) * v;

	VCoord x = v[0] / v[2];
	VCoord y = v[1] / v[2];

	Pixel halfDim;
	halfDim[0] = surfaceWidth/2;
	halfDim[1] = surfaceHeight/2;

	Pixel pixel;
	pixel[0] = halfDim[0] + x * halfDim[0];
	pixel[1] = halfDim[1] + y * halfDim[1];
	SetPixel(pixel, color);
}

void Renderer::Render(Line& line)
{
	Vector3D v1 = line.vtx0.vector;
	Color color1 = line.vtx0.color;

	Vector3D v2 = line.vtx1.vector;
	Color color2 = line.vtx1.color;
}

void Renderer::Render(Triangle& triangle)
{

}

void Renderer::SetPixel(Pixel p, Color c)
{
	//std::cout << "SetPixel(" << p[0] << "," << p[1] << "," << c << ")" << std::endl;
	surface.SetPixel(p[0], p[1], c.r, c.g, c.b);
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
