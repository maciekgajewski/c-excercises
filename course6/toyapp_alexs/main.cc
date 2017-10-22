#include <iostream>
#include <cmath>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/color.h>
#include <displaylib/cube.h>
#include <displaylib/transformation3d.h>

int main()
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", 10, 10, 800, 800);
	Display::Surface surf(200, 200);
	Display::Surface3D surf3d(surf);
	Display::Cube cube(Display::RED);

	surf3d.Clear(Display::BLUE);

	cube = cube.Transform(Display::Transformation3D()
						  .WithMoving({0.2, 0.1, 2})
						  .WithScaling({1, 1, 0.5}));

	cube.Draw(surf3d);
	win.Display(surf3d);

	Display::Delay(1000);

	auto rotation = Display::Transformation3D().WithRotation(0, 0, M_PI / 180);

	for (int i = 0; i <= 360 * 2; i++)
	{
		surf3d.Clear(Display::BLUE);

		cube = cube.Transform(rotation);

		cube.Draw(surf3d);
		win.Display(surf3d);

		Display::Delay(20);
	}

	return 0;
}
