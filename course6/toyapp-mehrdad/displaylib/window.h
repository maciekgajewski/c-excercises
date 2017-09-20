#pragma once

#include "sdlobject.h"
#include "types.h"

#include <SDL2/SDL.h>

#include <string>

namespace Display {

class Surface;

class Window : private SDLObject
{
public:

	Window(const std::string& title, Vector2D position, Size size);
	~Window();

	void Display(const Surface& surface);

private:

	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;

};

}
