#pragma once

namespace Display {

// A helper base class that uses global refcounter to cals SDL_Init/SDL_Quit
class SDLObject
{
public:
	SDLObject();
	~SDLObject();
};

}
