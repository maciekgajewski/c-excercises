#include "scene.h"

#include <cmath>
#include "surface.h"

namespace Display {

Scene::Scene(Surface3D& surface)
:	mSurface{surface},
	mTestCube1{{0.0f, 0.0f, 1.0f}, 1},
	mTestCube2{{1.25f, 0.25f, 1.0f}, 1},
	mTestCube3{{-1.25f, -0.25f, 1.0f}, 1}
{}

void Scene::Draw(double totalElapsedSeconds)
{
	Vector3D test = {std::sin(totalElapsedSeconds), 0, 1};
	camera.SetPosition(test);
	auto view = camera.CreateMatrix();
	mTestCube1.Draw(mSurface, view, Display::YELLOW);
	mTestCube2.Draw(mSurface, view, Display::YELLOW);
	mTestCube3.Draw(mSurface, view, Display::YELLOW);
}

}
