#include "window.h"

#include "surface.h"
#include <cassert>

namespace Display {

Window::Window(const char* title, int x, int y, int w, int h)
{
	mWindow = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
	assert(mWindow);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(mRenderer);
}

Window::~Window()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

void Window::Display(const Surface2D& surface)
{
	assert(surface.mSurface);
	SDL_RenderClear(mRenderer);

	auto* const tex = SDL_CreateTextureFromSurface(mRenderer, surface.mSurface);
	assert(tex);

	SDL_RenderCopy(mRenderer, tex, nullptr, nullptr);
	SDL_RenderPresent(mRenderer);
	SDL_DestroyTexture(tex);
}

}
