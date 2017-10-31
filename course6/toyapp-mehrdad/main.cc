#include <iostream>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/shapes2d.h>
#include <displaylib/shapes3d.h>

int main()
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", {10, 10}, {800, 600});
	Display::Surface surf({200, 150});
	Display::Color backgroud{200, 200, 200};
	Display::Color rotatedColor{200, 128, 180};

	surf.Clear(backgroud);
	Display::Rect r{{100, 100}, {30, 30}};
	r.Draw(surf, rotatedColor);
	for(int i = 0; i < 10; ++i)
	{
		win.Display(surf);
		Display::Delay(500);
		r.Rotate(-20);
		rotatedColor.mBlue -= 10;
		rotatedColor.mRed += 10;
		rotatedColor.mGreen -= 10;
		r.Draw(surf, rotatedColor);
	}

	Display::Delay(5000);

	surf.Clear(backgroud);
	Display::Cube cube;
	Display::Color cubeColor{100, 100, 100};
	cube.Draw(surf, cubeColor);

	win.Display(surf);
	Display::Delay(5000);

	return 0;
}
