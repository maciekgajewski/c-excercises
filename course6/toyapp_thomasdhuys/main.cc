#include <iostream>
#include <memory>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>

#include <drawlib/render_object.h>
#include <drawlib/primitives.h>
#include <drawlib/index.h>
#include <drawlib/drawer.h>

int main()
{
	std::cout << "Hello, here I am!" << std::endl;

	Draw::RenderObject ro = Draw::Drawer::Draw();

	ro.Print();

	for(int x = 0; x < 100; x++)
	{
//		surf.Clear(0, 0, 255); // blue background
//		surf.SetPixel(10+x, 10, 255, 0, 0); // red pixel at 10x10
//		win.Display(surf);
//		Display::Delay(50);
	}

//	Display::Delay(1000);

	return 0;
}
