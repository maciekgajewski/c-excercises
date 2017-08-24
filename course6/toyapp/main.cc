#include <iostream>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>

namespace {
	Display::Cube gCube({0, 0, 1.5f}, 1);
}

static void Draw(Display::Surface& surface)
{
	surface.DrawCube(gCube, Display::YELLOW);
}

int main()
{
	Display::Window win("Hello", 100, 100, 600, 600);
	Display::Surface surf(200, 200);

	SDL_Event e;
	bool quit = false;
	do
	{
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			else
			{
				surf.Clear(Display::BLUE);
				Draw(surf);
				win.Display(surf);
				Display::Delay(50);
			}

		}
	} while(!quit);

	return 0;
}
