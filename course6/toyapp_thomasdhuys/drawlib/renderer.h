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
	Renderer();
	void Render(Scenes& scenes);
private:
	// Methods
	Display::Window DefaultWindow();
	Display::Surface DefaultSurface();

	void Render(Scene& scene);
	void Render(Shape& shape);
	void Render(Point& point);
	void Render(Line& line);
	void Render(Triangle& triangle);

	void SetPixel(Pixel p, Color c);

	// Variables
	uint16_t surfaceWidth;
	uint16_t surfaceHeight;
	Display::Window window;
	Display::Surface surface;
};

}
