#pragma once

#include "cube.h"
#include "transform.h"

namespace Display {

class Surface3D;

class Scene
{
public:
	Scene(Surface3D& surface);

	void Draw(double totalElapsedSeconds);

	Transform camera;
private:
	Surface3D& mSurface;
	Cube mTestCube1;
	Cube mTestCube2;
	Cube mTestCube3;
};

}
