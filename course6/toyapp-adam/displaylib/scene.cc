#include "scene.h"

#include <cmath>
#include "surface.h"

namespace Display {

Scene::Scene(Keyboard& keyboard, Surface3D& surface)
:	mKeyboard{keyboard},
	mSurface{surface},
	mTestCube1{{0.0f, 0.0f, 2.0f}, 0.5f, Display::RED},
	mTestCube2{{1.25f, 0.25f, 2.0f}, 0.5f, Display::GREEN},
	mTestCube3{{-1.25f, -0.25f, 2.0f}, 0.5f, Display::YELLOW}
{}

void Scene::Update(double totalElapsedSeconds)
{
	constexpr float speed = 0.01f;
	Vector3D cameraMove;

	if(mKeyboard.IsDown(SDL_SCANCODE_LEFT))
		cameraMove.x = -speed;
	if(mKeyboard.IsDown(SDL_SCANCODE_RIGHT))
		cameraMove.x = +speed;
	if(mKeyboard.IsDown(SDL_SCANCODE_PAGEUP))
		cameraMove.y = +speed;
	if(mKeyboard.IsDown(SDL_SCANCODE_PAGEDOWN))
		cameraMove.y = -speed;
	if(mKeyboard.IsDown(SDL_SCANCODE_DOWN))
		cameraMove.z = -speed;
	if(mKeyboard.IsDown(SDL_SCANCODE_UP))
		cameraMove.z = +speed;

	mSurface.camera.transform.Move(cameraMove);

	float test1 = std::sin(totalElapsedSeconds);
	float test2 = std::cos(totalElapsedSeconds * 0.5f);

	mTestCube1.transform.Rotate(cameraMove * 1.5f);
	mTestCube2.transform.SetScale(0.25f + std::fabs(test1) * 0.5f);
	mTestCube2.transform.Rotate({0.0f, 0.001f, 0.0f});
	mTestCube3.transform.SetOrientation({0.0f, test1, test2});
}

void Scene::Draw()
{
	auto view = mSurface.camera.transform.CreateInverseMatrix();

	mTestCube1.Draw(mSurface, view);
	mTestCube2.Draw(mSurface, view);
	mTestCube3.Draw(mSurface, view);
}

}
