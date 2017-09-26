#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/objects.h>

#include <SDL2/SDL_main.h>

#include <iostream>


int main(int, char**)
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", 10, 10, 800, 600);
	Display::Surface surf(200, 150);

	Display::Color blue{0, 0, 255};

	surf.Clear(blue); // blue background

	Display::Vector3D activePoint{10, 10, 1};
	Display::Camera cam;
		

	for(int x = 0; x < 20; x++)
	{
		Display::Color red{255, 0, 0};

		//surf.SetPixel(cam.project2D(activePoint), red);
		surf.DrawLine(cam.project2D(activePoint), cam.project2D(activePoint + Display::Vector3D{10, 0, 0}), red);
		win.Display(surf);
		activePoint = activePoint + Display::Vector3D{0, 10, 0};
		
		Display::Delay(100);
	}

	Display::Delay(1000);

	return 0;
}
