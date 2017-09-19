#include "displaylib/window.h"
#include "displaylib/functions.h"
#include "displaylib/surface.h"
#include "displaylib/surface3d.h"
#include "displaylib/rgb.h"
#include "displaylib/cube.h"
#include "displaylib/pyramid.h"

#include <SDL2/SDL_main.h>

#include <iostream>


int main(int, char**)
{
	const auto h = 300, w = 400;

	Display::Window window("ToyApp - Mikhail",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w * 2, h * 2);

	Display::Surface surface2d(w, h);
	auto quit = false;

	auto start_x = w / 3, start_y = h / 3;

	auto backgroundColor = Display::RGB{ 190, 190, 190 };

	// 2d animation
	for (auto direction = -1; direction <= 1 && !quit; direction++)
	{
		for (auto y = 0; y < h / 3 && !quit; y++)
		{
			auto x = y * w / h;

			// background
			surface2d.Clear(backgroundColor);

			// Mark the center
			surface2d.SetPixel(w / 2, h / 2, 120, 255, 128);

			// Red moving cross
			surface2d.SetPixel(start_x + x, (3 - direction)*start_y / 2 + direction*y, 255, 0, 0);
			surface2d.SetPixel(start_x + x - 1, (3 - direction)*start_y / 2 + direction*y, 255, 0, 0);
			surface2d.SetPixel(start_x + x + 1, (3 - direction)*start_y / 2 + direction*y, 255, 0, 0);
			surface2d.SetPixel(start_x + x, (3 - direction)*start_y / 2 + direction*y - 1, 255, 0, 0);
			surface2d.SetPixel(start_x + x, (3 - direction)*start_y / 2 + direction*y + 1, 255, 0, 0);

			window.Display(surface2d);

			Display::PollEvents(quit);
			Display::Delay(5);
		}
	}

	// 3D animation
	auto cubeColor = Display::RGB{ 210, 10, 10 };
	auto pyramidColor = Display::RGB{ 10, 210, 10 };

	auto cube = Display::Cube{ Display::Matrix(), cubeColor };
	auto pyramid = Display::Pyramid{ Display::Matrix(), pyramidColor };

	auto surface3d = Display::Surface3D(surface2d);

	// Let user close window
	while (!quit)
	{
		surface2d.Clear(backgroundColor);

		cube.Draw(surface3d);
		pyramid.Draw(surface3d);
		window.Display(surface2d);

		Display::PollEvents(quit);
		Display::Delay(20);
	}
	return 0;
}
