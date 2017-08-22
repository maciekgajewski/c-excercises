#pragma once

#include <SDL2/SDL.h>

#include <string>

namespace Display {

class Window
{
public:

    Window(const std::string& title, int x, int y, int w, int h);

private:

    SDL_Window* mWindow = nullptr;

};

}