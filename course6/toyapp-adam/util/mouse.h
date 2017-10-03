#pragma once

#include "math/vector.h"
#include "pixel.h"

namespace Util {

using Math::Vector2D;

class Mouse
{
public:
	Mouse(Pixel::Coordinate physicalResolution)
	:	mScale{1.0f / static_cast<float>(physicalResolution)}
	{}

	Pixel GetCursorPosition() const { return mCursorPosition; }
	Pixel GetCursorPositionDelta() const { return mCursorPositionDelta; }
	Vector2D GetPositionDelta() const { return mPositionDelta; }

	void AddDeltaPosition(Pixel delta)
	{
		mCursorPositionDelta.x += delta.x;
		mCursorPositionDelta.y += delta.y;
		mPositionDelta[0] = mCursorPositionDelta.x * mScale;
		mPositionDelta[1] = mCursorPositionDelta.y * mScale;
	}

	void RecordPosition()
	{
		mCursorPosition.x += mCursorPositionDelta.x;
		mCursorPosition.y += mCursorPositionDelta.y;
		mCursorPositionDelta = {};
		mPositionDelta = {};
	}
private:
	Pixel mCursorPosition;
	Pixel mCursorPositionDelta;
	Vector2D mPositionDelta;
	float mScale;
};

}
