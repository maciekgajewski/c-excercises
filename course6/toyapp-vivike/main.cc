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

	Display::Vector2D activePixel;
	activePixel.x = 10;
	activePixel.y = 10;
		

	for(int x = 0; x < 20; x++)
	{
		Display::Color red{255, 0, 0};

		surf.SetPixel(activePixel, red); // red pixel at 10x10
		activePixel.move(1, 0);
		win.Display(surf);
		Display::Delay(200);
	}

	Display::Delay(5000);

	return 0;
}
