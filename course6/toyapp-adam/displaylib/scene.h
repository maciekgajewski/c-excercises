#pragma once

#include "cube.h"
#include "transform.h"

namespace Display {

class Keyboard;
class Surface3D;

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
