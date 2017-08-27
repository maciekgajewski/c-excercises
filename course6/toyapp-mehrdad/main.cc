#include <iostream>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>


int main()
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", {10, 10}, {800, 600});
	Display::Surface surf({200, 150});
	Display::Color backgroud{0, 0, 255};
	Display::Color pixelColor{255, 0, 0};

	surf.Clear(backgroud);
	Display::Vector2D v1{10, 10};
	Display::Vector2D v2{100, 10};
	surf.DrawLine(v1, v2, pixelColor);
	surf.SetPixel(v1, {0, 0, 0});
	surf.SetPixel(v2, {0, 0, 0});
	win.Display(surf);
	Display::Delay(5000);

	return 0;
}
