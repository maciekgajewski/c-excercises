#include <iostream>

#include <displaylib/clock.h>
#include <displaylib/scene.h>
#include <displaylib/surface.h>
#include <displaylib/window.h>
#include <SDL2/SDL_main.h>

int main(int argc, char* argv[])
{
	Display::Window win("Hello", 100, 100, 800, 800);
	Display::Surface2D surface2D(800, 800);
	Display::Surface3D surface3D(surface2D);
	Display::Scene scene(surface3D);
	Display::Clock clock;

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
		}

		surface2D.Clear(Display::BLUE);
		scene.Draw(clock.GetTotalElapsedSeconds());
		win.Display(surface2D);

	} while(!quit);

	return 0;
}
