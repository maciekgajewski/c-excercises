#pragma once

#include "sdlobject.h"
#include "surface.h"
#include "surface3d.h"

#include <SDL2/SDL.h>

#include <string>

namespace Display {

class Surface;

class Window : private SDLObject
{
public:

	Window(const std::string& title, int x, int y, int w, int h);
	~Window();

	void Display(const Surface& surface);
	void Display(const Surface3D& surface);

private:

	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;

};

}
