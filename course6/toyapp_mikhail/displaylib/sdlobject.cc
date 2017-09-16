#include "sdlobject.h"

#include <SDL2/SDL.h>

#include <cassert>

namespace Display {

static unsigned objectCounter = 0;

SDLObject::SDLObject()
{
	if (objectCounter == 0)
	{
		int res = SDL_Init(SDL_INIT_VIDEO);
		assert(res == 0);
	}
	objectCounter++;
}

SDLObject::~SDLObject()
{
	objectCounter--;
	if (objectCounter == 0)
		SDL_Quit();
}

}
