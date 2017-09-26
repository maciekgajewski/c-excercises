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

	Display::Vector2D activePixel{10, 10};
		

	for(int x = 0; x < 20; x++)
	{
		Display::Color red{255, 0, 0};

		//surf.SetPixel(activePixel, red); // red pixel at 10x10
		surf.DrawLine(activePixel, activePixel + Display::Vector2D{0, 5}, red);
		win.Display(surf);
		activePixel = activePixel + Display::Vector2D{x, 0};
		
		Display::Delay(100);
	}

	Display::Delay(1000);

	return 0;
}
