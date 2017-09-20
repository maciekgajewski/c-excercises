#pragma once

#include <displaylib/cube.h>

namespace Display {
	class Surface3D;
}

namespace Util {
	class Keyboard;
	class Mouse;
}

using Display::Cube;
using Display::Surface3D;
using Util::Keyboard;
using Util::Mouse;

class Scene
{
public:
	Scene(Keyboard& keyboard, Mouse& mouse, Surface3D& surface);

	void Update(double totalElapsedSeconds);
	void Draw();
private:
	Keyboard& mKeyboard;
	Mouse& mMouse;
	Surface3D& mSurface;
	Cube mTestCube1;
	Cube mTestCube2;
	Cube mTestCube3;
	Cube mTestCube4;
	Cube mTestCube5;
};
