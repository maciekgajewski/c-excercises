#pragma once

#include "math/vector.h"
#include "pixel.h"

namespace Util {

using Math::Vector2D;

class Mouse
{
public:
	Mouse(Pixel::Component physicalResolution)
	:	mScale{1.0f / static_cast<float>(physicalResolution)}
	{}

	Pixel GetCursorPosition() const { return mCursorPosition; }
	Pixel GetCursorPositionDelta() const { return mCursorPositionDelta; }
	Vector2D GetPositionDelta() const { return mPositionDelta; }

	void AddDeltaPosition(Pixel delta)
	{
		mCursorPositionDelta[0] += delta[0];
		mCursorPositionDelta[1] += delta[1];
		mPositionDelta[0] = mCursorPositionDelta[0] * mScale;
		mPositionDelta[1] = mCursorPositionDelta[1] * mScale;
	}

	void RecordPosition()
	{
		mCursorPosition[0] += mCursorPositionDelta[0];
		mCursorPosition[1] += mCursorPositionDelta[1];
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
