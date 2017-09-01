#include <iostream>

#include <displaylib/cube.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/window.h>
#include <SDL2/SDL_main.h>

namespace {
	Display::Cube gCube({0, 0, 1.5f}, 1);
}

static void DrawScene(Display::Surface3D& surface)
{
	gCube.Draw(surface, Display::YELLOW);
}

int main(int argc, char* argv[])
{
	Display::Window win("Hello", 100, 100, 800, 800);
	Display::Surface2D surface2D(800, 800);
	Display::Surface3D surface3D(surface2D);

	SDL_Event e;
	bool quit = false;
	do
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			else
			{
				surface2D.Clear(Display::BLUE);
				DrawScene(surface3D);
				win.Display(surface2D);
				Display::Delay(50);
			}
		}
	} while(!quit);

	return 0;
}
