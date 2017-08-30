#include <iostream>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/point2d.h>
#include <displaylib/point3d.h>
#include <displaylib/color.h>

int main()
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", 10, 10, 800, 600);
	Display::Surface surf(200, 150);

	Display::Color blue(0, 0, 255);
	Display::Color red(255, 0, 0);

	for(int x = 0; x < 100; x++)
	{
		surf.Clear(blue);
		Display::Point2D point(10+x, 10);
		surf.SetPixel(point, red);
		win.Display(surf);
		Display::Delay(50);
	}

	Display::Delay(1000);

	return 0;
}
