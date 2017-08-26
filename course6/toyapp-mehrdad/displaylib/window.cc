#include "window.h"

#include "surface.h"

#include <cassert>

namespace Display {

Window::Window(const std::string& title, Vector2D pos, Size size)
{
	mWindow = SDL_CreateWindow(title.c_str(), pos.mX, pos.mY,
							   size.mWidth, size.mHeight, SDL_WINDOW_SHOWN);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
}

Window::~Window()
{
	if (mRenderer)
		SDL_DestroyRenderer(mRenderer);

	if (mWindow)
		SDL_DestroyWindow(mWindow);
}

void Window::Display(const Surface& surface)
{
	assert(mRenderer);
	assert(mWindow);
	assert(surface.mSurface);

	SDL_RenderClear(mRenderer);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface.mSurface);
	assert(tex);

	SDL_RenderCopy(mRenderer, tex, nullptr, nullptr);
	SDL_RenderPresent(mRenderer);
	SDL_DestroyTexture(tex);
}


}
