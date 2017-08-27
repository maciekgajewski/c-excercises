#pragma once

#include <stdint.h>
#include <vector>

namespace Display {

struct Vector2D
{
	int mX;
	int mY;
};

struct Vector3D
{
	int mX;
	int mY;
	int mZ;
};

using Polygon = std::vector<Vector2D>;
using Polyhedron = std::vector<Vector3D>;
using Degree = double;
using Radian = double;

struct Size
{
	int mWidth;
	int mHeight;
};

struct Rect
{
	Vector2D mTopLeft;
	Size mSize;
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

inline Vector2D operator+(Vector2D v1, Vector2D v2)
{
	return {v1.mX + v2.mX, v1.mY + v2.mY};
}
}
