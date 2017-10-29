#include "sdlobject.h"

#include <SDL2/SDL.h>
#include <cassert>

namespace Display {

namespace {
	unsigned gOjectCounter = 0;
}

SDLObject::SDLObject()
{
	if(gOjectCounter++ == 0)
	{
		auto res = SDL_Init(SDL_INIT_VIDEO);
		assert(res == 0);
	}
}

SDLObject::~SDLObject()
{
	if(--gOjectCounter == 0)
		SDL_Quit();
}

}
