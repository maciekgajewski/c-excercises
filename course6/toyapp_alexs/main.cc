#include <iostream>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/vector2d.h>
#include <displaylib/vector3d.h>
#include <displaylib/color.h>
#include <displaylib/cube.h>
#include <displaylib/transformation3d.h>

int main()
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", 10, 10, 800, 600);
	Display::Surface surf(200, 150);
	Display::Surface3D surf3d(surf);
	Display::Cube cube(Display::RED);

	surf3d.Clear(Display::BLUE);
	cube.Draw(surf3d);
	win.Display(surf3d);

	Display::Delay(2000);

	surf3d.Clear(Display::BLUE);
	cube = cube.Transform(Display::Move3D({0, 0, 2}));
	cube.Draw(surf3d);
	win.Display(surf3d);

	Display::Delay(2000);

	surf3d.Clear(Display::BLUE);
	cube = cube
		.Transform(Display::Scale3D({1, 1, 5}))
		.Transform(Display::Move3D({0, 0, -4}));
	cube.Draw(surf3d);
	win.Display(surf3d);

	Display::Delay(2000);

	return 0;
}
