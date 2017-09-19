#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>

#include <SDL2/SDL_main.h>

#include <iostream>


int main(int, char**)
{
	const auto h = 300, w = 400;

	Display::Window window("ToyApp - Mikhail",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w * 2, h * 2);

	Display::Surface surf(w, h);
	auto quit = false;

	auto start_x = w / 3, start_y = h / 3;

	for (auto direction = -1; direction <= 1 && !quit; direction++)
	{
		for (auto y = 0; y < h / 3 && !quit; y++)
		{
			auto x = y * w / h;

			// background
			surf.Clear(190, 190, 190);

			// Mark the center
			surf.SetPixel(w / 2, h / 2, 120, 255, 128);

			// Red moving cross
			surf.SetPixel(start_x + x, (3 - direction)*start_y / 2 + direction*y, 255, 0, 0);
			surf.SetPixel(start_x + x - 1, (3 - direction)*start_y / 2 + direction*y, 255, 0, 0);
			surf.SetPixel(start_x + x + 1, (3 - direction)*start_y / 2 + direction*y, 255, 0, 0);
			surf.SetPixel(start_x + x, (3 - direction)*start_y / 2 + direction*y - 1, 255, 0, 0);
			surf.SetPixel(start_x + x, (3 - direction)*start_y / 2 + direction*y + 1, 255, 0, 0);

			window.Display(surf);

			Display::PollEvents(quit);
			Display::Delay(20);
		}
	}

	// Let user close window
	while (!quit)
	{
		Display::PollEvents(quit);
		Display::Delay(10);
	}
	return 0;
}
