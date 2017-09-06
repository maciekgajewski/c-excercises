#include <iostream>
#include <memory>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>

#include <drawlib/renderer.h>
#include <drawlib/render_object.h>
#include <drawlib/primitives.h>
#include <drawlib/index.h>
#include <drawlib/drawer.h>

int main()
{
	std::cout << "Hello, here I am!" << std::endl;

	Draw::Renderer r = Draw::Renderer();
	Draw::RenderObject ro = Draw::Drawer::Draw();

	ro.Print();

	r.Render(ro);

	return 0;
}
