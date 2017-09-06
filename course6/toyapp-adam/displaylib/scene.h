#pragma once

#include "cube.h"

namespace Util {
	class Keyboard;
	class Mouse;
}

namespace Display {

class Surface3D;
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

}
