#pragma once

#include "pixel.h"

namespace Util {

class Mouse
{
public:
	Pixel GetCursorPosition() const { return mCursorPosition; }
	Pixel GetCursorPositionDelta() const { return mCursorPositionDelta; }

	void AddDeltaPosition(Pixel delta)
	{
		mCursorPositionDelta.x += delta.x;
		mCursorPositionDelta.y += delta.y;
	}

	void RecordPosition()
	{
		mCursorPosition.x += mCursorPositionDelta.x;
		mCursorPosition.y += mCursorPositionDelta.y;
		mCursorPositionDelta = {0, 0};
	}
private:
	Pixel mCursorPosition = {0, 0};
	Pixel mCursorPositionDelta = {0, 0};
};

}
