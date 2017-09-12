#pragma once

#include <cstdint>
#include <vector>

#include <displaylib/surface.h>
#include <displaylib/window.h>
#include <displaylib/functions.h>

#include "primitives.h"
#include "render_object.h"
#include "pixel.h"

namespace Draw {

class Renderer {
public:
	Renderer();
	void Render(RenderObject& ro);
private:
	Display::Window DefaultWindow();
	Display::Surface DefaultSurface();
	Display::Window window;
	Display::Surface surface;

	void Render(const Point& point);
	void Render(const Line& line);
	void Render(const Triangle& triangle);
	void SetPixel(Pixel p, RGB c); 

	uint16_t surfaceWidth;
	uint16_t surfaceHeight;
};

}
