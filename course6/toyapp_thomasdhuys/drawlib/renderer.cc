#include "renderer.h"

namespace Draw {

void Renderer::Render(RenderObject& ro)
{
	for (const auto& prim_ptr : *ro.GetData())
	{
//		Display::Delay(500);
	}
}

Renderer::Renderer() { //: window(DefaultWindow()), surface(DefaultSurface()) {
	surfaceWidth  = 200;
	surfaceHeight = 150;
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
