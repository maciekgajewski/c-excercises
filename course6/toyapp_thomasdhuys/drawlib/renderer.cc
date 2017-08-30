#include "renderer.h"

namespace Draw {
namespace Render {

void Renderer::Render(RenderObject ro)
{
	for (const auto& prim : *ro.GetData())
	{

	}
}

Renderer::Renderer(): window(DefaultWindow()), surface(DefaultSurface()) {}

Display::Window Renderer::DefaultWindow()
{
	return Display::Window("Hello", 10, 10, 800, 600);
}

Display::Surface Renderer::DefaultSurface()
{
	return Display::Surface(200,150);
}


}
}
