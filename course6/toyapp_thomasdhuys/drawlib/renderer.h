#pragma once

#include <cstdint>
#include <vector>

#include <displaylib/surface.h>
#include <displaylib/window.h>
#include <displaylib/functions.h>

#include "primitives.h"
#include "render_object.h"

namespace Draw {

class Renderer {
public:
	Renderer();
	void Render(RenderObject ro);
private:
	Display::Window DefaultWindow();
	Display::Surface DefaultSurface();
	Display::Window window;
	Display::Surface surface;
};

}
