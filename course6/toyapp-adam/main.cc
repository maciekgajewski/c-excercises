#include <iostream>

#include <displaylib/scene.h>
#include <displaylib/surface.h>
#include <displaylib/window.h>
#include <util/clock.h>
#include <util/keyboard.h>
#include <util/mouse.h>
#include <SDL2/SDL_main.h>

int main(int argc, char* argv[])
{
	Util::Keyboard keyboard;
	Util::Mouse mouse;
	Util::Clock clock;

	Display::Window win("Hello", 100, 100, 1280, 720);
	Display::Surface2D surface2D(640, 360);
	Display::Surface3D surface3D(surface2D);
	Display::Scene scene(keyboard, mouse, surface3D);

	SDL_Event e;
	SDL_SetRelativeMouseMode(SDL_TRUE);

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
				case SDL_MOUSEMOTION:
					mouse.AddDeltaPosition({e.motion.xrel, e.motion.yrel});
				break;
				case SDL_QUIT:
					quit = true;
				break;
			}
		}

		surface2D.Clear(Display::BLACK);
		scene.Update(clock.GetTotalElapsedSeconds());
		scene.Draw();
		win.Display(surface2D);

		keyboard.ClearChanges();
		mouse.RecordPosition();

	} while(!quit);

	return 0;
}
