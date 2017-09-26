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

	Display::Rectangle rect{{100, 100, 1}, {100, 150, 1}, {150, 150, 1}, {150, 100, 1}};
	Display::Camera cam;
		

	for(int x = 0; x < 20; x++)
	{
		Display::Color red{255, 0, 0};

		surf.Clear(blue); // blue background
		
		surf.DrawLine(cam.project2D(rect.corner1), cam.project2D(rect.corner2), red);
		surf.DrawLine(cam.project2D(rect.corner2), cam.project2D(rect.corner3), red);
		surf.DrawLine(cam.project2D(rect.corner3), cam.project2D(rect.corner4), red);
		surf.DrawLine(cam.project2D(rect.corner4), cam.project2D(rect.corner1), red);
		
		win.Display(surf);
		rect = rect.move({0, 0, 1});
		
		Display::Delay(100);
	}

	Display::Delay(1000);

	return 0;
}
