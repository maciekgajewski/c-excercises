#include "renderer.h"

#include <iostream>

namespace Draw {

void Renderer::Render(RenderObject& ro)
{
	for (const auto& prim_ptr : *ro.GetData())
	{
		RenderPoint(dynamic_cast<Point&>(*prim_ptr));
		std::cout << *prim_ptr << std::endl;
	}
}

Renderer::Renderer(): window(DefaultWindow()), surface(DefaultSurface()) {
	surfaceWidth  = 200;
	surfaceHeight = 150;
}

void Renderer::RenderPoint(const Point& point)
{
	Vector3D v = point.idx0->vector;
	RGB color = point.idx0->color;

	Pixel pixel;
	pixel.x = v.x;
	pixel.y = v.y;
	SetPixel(pixel, color);
}

void Renderer::SetPixel(Pixel p, RGB c)
{
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
