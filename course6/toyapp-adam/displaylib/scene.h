#pragma once

#include "cube.h"
#include "math/transform.h"
#include "util/keyboard.h"

namespace Display {

class Surface3D;
using Math::Transform;
using Util::Keyboard;

class Scene
{
public:
	Scene(Keyboard& keyboard, Surface3D& surface);

	void Update(double totalElapsedSeconds);
	void Draw();

	Transform camera;
private:
	Keyboard& mKeyboard;
	Surface3D& mSurface;
	Cube mTestCube1;
	Cube mTestCube2;
	Cube mTestCube3;
};

}
