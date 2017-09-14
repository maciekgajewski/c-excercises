#include "functions.h"

#include <SDL2/SDL.h>

namespace Display {

	void Delay(int msec)
	{
		SDL_Delay(msec);
	}

	void PollEvents(bool& quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}
