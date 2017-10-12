#pragma once

#include "sdlobject.h"
#include "rgb.h"
#include "vector_common.h"

#include <cstdint>
#include <cmath>

#include <SDL2/SDL.h>

namespace Display {

	class Surface : private SDLObject
	{
	public:
		Surface(int w, int h);
		~Surface();

		void Clear(RGB color);

		void SetPixel(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
		void SetPixel(int x, int y, RGB color) { SetPixel(x, y, color.r, color.g, color.b); }
		void SetPixel(Vector2D p, RGB color) { SetPixel((int)std::round(p.x), (int)std::round(p.y), color.r, color.g, color.b); }

		void DrawLine(Vector2D start, Vector2D end, RGB color);

		int GetH();
		int GetW();

	private:

		friend class Window;
		SDL_Surface* mSurface;
	};

};