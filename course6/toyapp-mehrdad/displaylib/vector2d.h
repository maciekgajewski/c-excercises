#pragma once

#include "types.h"

namespace Display {


struct Vector2D
{
	double mX;
	double mY;

	Pixel ToPixel() { return {static_cast<int>(mX), static_cast<int>(mY)}; }
};

}
