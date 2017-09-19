#include "surface.h"

#include <cassert>
#include <cmath>
#include <utility>

namespace Display {

	Surface::Surface(int w, int h)
	{
		mSurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	}

	Surface::~Surface()
	{
		if (mSurface)
			SDL_FreeSurface(mSurface);
	}

	void Surface::Clear(RGB color)
	{
		assert(mSurface);

		for (int y = 0; y < mSurface->h; y++)
			for (int x = 0; x < mSurface->w; x++)
				SetPixel(x, y, color.r, color.g, color.b);
	}

	void Surface::SetPixel(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b)
	{
		assert(mSurface);

		if (x < 0 || y < 0 || x >= mSurface->w || y > mSurface->h)
			return;

		std::uint32_t pixelValue = (std::uint32_t(r) << 16) + (std::uint32_t(g) << 8) + b;

		std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (y*mSurface->pitch / 4 + x);
		*pixelAddr = pixelValue;
	}

	void Surface::DrawLine(Vector2D start, Vector2D end, RGB color)
	{
		auto x1 = (int)std::round(start.x);
		auto x2 = (int)std::round(end.x);
		auto y1 = (int)std::round(start.y);
		auto y2 = (int)std::round(end.y);

		if (std::abs(x1 - x2) > std::abs(y1 - y2))
		{
			if (x1 > x2) {
				std::swap(x1, x2);
				std::swap(y1, y2);
			}

			auto ratio = (x1 == x2) ? 1.0 : 1.0*(y1 - y2) / (x1 - x2);
			for (auto x = x1; x <= x2; ++x)
			{
				auto y = (int)std::round(y1 + ratio * (x-x1));
				SetPixel( x, y , color);
			}
		}
		else
		{
			if (y1 > y2) {
				std::swap(x1, x2);
				std::swap(y1, y2);
			}

			auto ratio = (y1 == y2) ? 1.0 : 1.0*(x1 - x2) / (y1 - y2);
			for (auto y = y1; y <= y2; ++y)
			{
				auto x = (int) x1 + ratio * (y - y1);
				SetPixel(x, y , color);
			}
		}
	}

	int Display::Surface::GetW()
	{
		assert(mSurface);
		return mSurface->w;
	}

	int Display::Surface::GetH()
	{
		assert(mSurface);
		return mSurface->h;
	}
}
