#include <iostream>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>

int main()
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", 10, 10, 800, 600);
	Display::Surface surf(200, 150);

	for(int x = 0; x < 100; x++)
	{
		surf.Clear(0, 0, 255); // blue background
		surf.SetPixel(10+x, 10, 255, 0, 0); // red pixel at 10x10
		win.Display(surf);
		Display::Delay(50);
	}

	Display::Delay(1000);

	return 0;
}
