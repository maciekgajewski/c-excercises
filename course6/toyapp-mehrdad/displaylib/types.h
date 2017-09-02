#pragma once

#include <stdint.h>
#include <vector>

namespace Display {

struct Pixel
{
	int mX;
	int mY;
};

using Degree = double;
using Radian = double;

struct Size
{
	int mWidth;
	int mHeight;
};

struct Color
{
	uint8_t mRed;
	uint8_t mGreen;
	uint8_t mBlue;
};

}
