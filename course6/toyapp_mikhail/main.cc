#include "displaylib/window.h"
#include "displaylib/functions.h"
#include "displaylib/surface.h"
#include "displaylib/surface3d.h"
#include "displaylib/rgb.h"
#include "displaylib/cube.h"
#include "displaylib/pyramid.h"
#include "displaylib/shape.h"

#include <SDL2/SDL_main.h>

#include <iostream>


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <SHAPE_FILE>" << std::endl;
		return 1;
	}

	const auto h = 600, w = 800;

	Display::Window window("ToyApp - Mikhail",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w, h);

	Display::Surface surface2d(w, h);
	auto quit = false;
	auto backgroundColor = Display::RGB{ 190, 190, 190 };
	auto cubeColor = Display::RGB{ 210, 10, 10 };
	auto pyramidColor = Display::RGB{ 10, 210, 10 };
	auto shapeColor = Display::RGB{ 10, 50, 210 };

	auto cube = Display::Cube{ Display::Matrix(), cubeColor };
	auto pyramid = Display::Pyramid{ Display::Matrix(), pyramidColor };

	auto surface3d = Display::Surface3D(surface2d);
	surface2d.Clear(backgroundColor);
	window.Display(surface2d);

	// Shape
	auto shape = Display::Shape::LoadFromFile(argv[1]);
	shape.SetColor(shapeColor);

	// Let user close window
	long time = 0;
	while (!quit)
	{
		surface2d.Clear(backgroundColor);

		if (time < 500 && time > 0)
			cube.Draw(surface3d);
		if (time < 750 && time > 250)
			pyramid.Draw(surface3d);
		if (time > 1000)
			shape.Draw(surface3d);

		window.Display(surface2d);

		Display::PollEvents(quit);
		Display::Delay(20);
		time += 20;

		if (time > 2000)
			time = 0;
	}
	return 0;
}
