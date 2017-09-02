#pragma once

#include <stdint.h>
#include <vector>

namespace Display {

struct Pixel
{
	int mX;
	int mY;
};

struct Vector2D
{
	double mX;
	double mY;

	Pixel ToPixel() { return {static_cast<int>(mX), static_cast<int>(mY)}; }
};

struct Vector3D
{
	double mX;
	double mY;
	double mZ;
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
