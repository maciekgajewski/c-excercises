#include <iostream>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/vector2d.h>
#include <displaylib/vector3d.h>
#include <displaylib/color.h>
#include <displaylib/cube.h>

int main()
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", 10, 10, 800, 600);
	Display::Surface surf(200, 150);

	surf.Clear(Display::BLUE);

	Display::Cube cube({0, 0, 1}, Display::RED,1);
	cube.Draw(surf);

	win.Display(surf);

	// for(int x = 0; x < 100; x++)
	// {
	// 	surf.Clear(blue);
	// 	surf.SetPixel({10+x, 10}, red);
	// 	win.Display(surf);
	// 	Display::Delay(50);
	// }

	Display::Delay(5000);

	return 0;
}
