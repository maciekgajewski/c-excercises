#include <iostream>

#include <displaylib/scene.h>
#include <displaylib/surface.h>
#include <displaylib/window.h>
#include <util/clock.h>
#include <util/keyboard.h>
#include <SDL2/SDL_main.h>

int main(int argc, char* argv[])
{
	Util::Keyboard keyboard;
	Util::Clock clock;

	Display::Window win("Hello", 100, 100, 800, 800);
	Display::Surface2D surface2D(800, 800);
	Display::Surface3D surface3D(surface2D);
	Display::Scene scene(keyboard, surface3D);

	SDL_Event e;
	bool quit = false;
	do
	{
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_KEYDOWN:
					keyboard.Press(SDL_GetScancodeFromKey(e.key.keysym.sym));
				break;
				case SDL_KEYUP:
					keyboard.Release(SDL_GetScancodeFromKey(e.key.keysym.sym));
				break;
				case SDL_QUIT:
					quit = true;
				break;
			}
		}

		surface2D.Clear(Display::BLUE);
		scene.Update(clock.GetTotalElapsedSeconds());
		scene.Draw();
		win.Display(surface2D);
		keyboard.ClearChanges();

	} while(!quit);

	return 0;
}
