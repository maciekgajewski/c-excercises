#include "keyboard.h"

#include <cassert>

namespace Display {

void Keyboard::Press(KeyCode keyCode)
{
	assert(keyCode >= 0);
	assert(keyCode < NUM_KEYCODES);

	mKeys[keyCode].up = 0;
	mKeys[keyCode].down = 1;
	mKeys[keyCode].pressed = 1;
}

void Keyboard::Release(KeyCode keyCode)
{
	assert(keyCode >= 0);
	assert(keyCode < NUM_KEYCODES);

	mKeys[keyCode].up = 1;
	mKeys[keyCode].down = 0;
	mKeys[keyCode].released = 1;
}

void Keyboard::ClearChanges()
{
	for(KeyCode i = 0; i < NUM_KEYCODES; ++i)
	{
		mKeys[i].pressed = 0;
		mKeys[i].released = 0;
	}
}

bool Keyboard::IsUp(KeyCode keyCode) const
{
	assert(keyCode >= 0);
	assert(keyCode < NUM_KEYCODES);

	return mKeys[keyCode].up;
}

bool Keyboard::IsDown(KeyCode keyCode) const
{
	assert(keyCode >= 0);
	assert(keyCode < NUM_KEYCODES);

	return mKeys[keyCode].down;
}

bool Keyboard::IsPressed(KeyCode keyCode) const
{
	assert(keyCode >= 0);
	assert(keyCode < NUM_KEYCODES);

	return mKeys[keyCode].pressed;
}

bool Keyboard::IsReleased(KeyCode keyCode) const
{
	assert(keyCode >= 0);
	assert(keyCode < NUM_KEYCODES);

	return mKeys[keyCode].released;
}

}
