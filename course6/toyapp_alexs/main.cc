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
	Display::Surface3D surf3d(surf);

	surf3d.Clear(Display::BLUE);

	Display::Cube cube({0, 0, 1}, Display::RED,1);
	cube.Draw(surf3d);
 
	win.Display(surf3d);

	Display::Delay(5000);

	return 0;
}
