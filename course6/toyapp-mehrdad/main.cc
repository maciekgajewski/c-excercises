#include <iostream>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>

int main()
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", {10, 10}, {800, 600});
	Display::Surface surf({200, 150});
	Display::Color backgroud{200, 200, 200};
	Display::Color rectColor{255, 0, 0};
	Display::Color rotatedColor{200, 128, 180};

	surf.Clear(backgroud);
	Display::Rect r{{100, 23}, {30, 30}};
	surf.DrawRect(r, rectColor);
	surf.DrawRect(r, 20, rotatedColor);
	surf.DrawRect(r, 70, rotatedColor);

	win.Display(surf);
	Display::Delay(2000);

	Display::Color cubeColor{100, 100, 100};
//	surf.Clear(backgroud);
	Display::Polyhedron cube {{200, 200, 10}, {200, 430, 10}, {430, 430, 10}, {430, 200, 10},
							  {200, 200, 20}, {200, 430, 20}, {430, 430, 20}, {430, 200, 20}};
	surf.DrawCube(cube, cubeColor);
	for (auto pp: cube)
		surf.SetPixel(Render(pp), {0, 0, 0});

	win.Display(surf);
	Display::Delay(5000);

	return 0;
}
