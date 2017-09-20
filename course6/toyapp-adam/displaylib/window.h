#pragma once

#include "sdlobject.h"
#include <SDL2/SDL.h>

namespace Display {

class Surface2D;

class Window : private SDLObject
{
public:
	Window(const char* title, int x, int y, int w, int h);
	~Window();

	void Display(const Surface2D& surface);
private:
	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;

};

}
