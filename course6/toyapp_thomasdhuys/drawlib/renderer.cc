#include "renderer.h"

#include <iostream>

namespace Draw {

void Renderer::Render(RenderObject& ro)
{
	for (const auto& prim_ptr : *ro.GetData())
	{
		std::cout << *prim_ptr << std::endl;
		Render(dynamic_cast<Point&>(*prim_ptr));
	}
}

Renderer::Renderer(): window(DefaultWindow()), surface(DefaultSurface()) {
	surfaceWidth  = 200;
	surfaceHeight = 150;
}

void Renderer::Render(const Point& point)
{
	Vector3D v = point.idx0->vector;
	RGB color = point.idx0->color;

	Pixel pixel;
	pixel.x = v.x * surfaceWidth/2;
	pixel.y = v.y * surfaceHeight/2;
	SetPixel(pixel, color);
}

void Renderer::Render(const Line& line)
{
	Vector3D v1 = line.idx0->vector;
	RGB color1 = line.idx0->color;

	Vector3D v2 = line.idx1->vector;
	RGB color2 = line.idx1->color;

	Pixel pixel;
	pixel.x = v1.x;
	pixel.y = v2.y;
	SetPixel(pixel, color1);
}

void Renderer::Render(const Triangle& triangle)
{

}

void Renderer::SetPixel(Pixel p, RGB c)
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
	return Display::Surface(200,150);
}

}
