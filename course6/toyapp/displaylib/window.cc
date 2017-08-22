#include "window.h"

namespace Display {

Window::Window(const std::string& title, int x, int y, int w, int h)
{
    mWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
}

}
