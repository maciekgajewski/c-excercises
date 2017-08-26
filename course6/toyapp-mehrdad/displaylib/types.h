#pragma once

#include <stdint.h>

namespace Display {

struct Vector2D
{
	int mX;
	int mY;
};

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

	uint32_t GetPixelValue() const;
};

inline uint32_t Color::GetPixelValue() const
{
    return (uint32_t(mRed)<<16) + (uint32_t(mGreen)<<8) + mBlue;
}
}
