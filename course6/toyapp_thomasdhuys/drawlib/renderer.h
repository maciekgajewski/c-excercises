#pragma once

#include <cstdint>
#include <vector>

#include <displaylib/surface.h>
#include <displaylib/window.h>
#include <displaylib/functions.h>

#include "primitives.h"
#include "scene.h"
#include "pixel.h"

namespace Draw {

class Renderer {
public:
	Renderer(int surfaceWidth, int surfaceHeight);
	void Render(Scenes& scenes);
private:
	// Methods
	Display::Window DefaultWindow();
	Display::Surface DefaultSurface();

	void Render(const Point& point);
	void Render(const Line& line);
	void Render(const Triangle& triangle);
	void SetPixel(Pixel p, Color c); 

	// Variables
	uint16_t surfaceWidth;
	uint16_t surfaceHeight;
	Display::Window window;
	Display::Surface surface;
};

}
