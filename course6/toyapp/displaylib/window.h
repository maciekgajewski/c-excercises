#pragma once

#include "sdlobject.h"
#include "sdl.h"

#include <string>

namespace Display {

class Surface;

class Window : private SDLObject
{
public:

	Window(const std::string& title, int x, int y, int w, int h);
	~Window();

	void Display(const Surface& surface);

private:

	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;

};

}
