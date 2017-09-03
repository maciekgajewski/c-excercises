#include "scene.h"

#include <cmath> // for test: sin and cos
#include "keyboard.h"
#include "surface.h"

namespace Display {

Scene::Scene(Keyboard& keyboard, Surface3D& surface)
:	mKeyboard{keyboard},
	mSurface{surface},
	mTestCube1{{0.0f, 0.0f, 1.0f}, 0.5f, Display::YELLOW},
	mTestCube2{{1.25f, 0.25f, 1.0f}, 0.5f, Display::YELLOW},
	mTestCube3{{-1.25f, -0.25f, 1.0f}, 0.5f, Display::YELLOW}
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

	camera.Move(cameraMove);

	float test = std::fabs(std::sin(totalElapsedSeconds * 1.0f));
	mTestCube2.transform.SetScale(0.25f + test * 0.5f);
}

void Scene::Draw()
{
	auto view = camera.CreateInverseMatrix();

	mTestCube1.Draw(mSurface, view);
	mTestCube2.Draw(mSurface, view);
	mTestCube3.Draw(mSurface, view);
}

}
