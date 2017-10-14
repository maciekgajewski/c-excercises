#include "scene.h"

#include <displaylib/mesh_util.h>
#include <displaylib/surface_3d.h>
#include <util/keyboard.h>
#include <util/mouse.h>

Scene::Scene(Keyboard& keyboard, Mouse& mouse, Surface3D& surface)
:	mKeyboard{keyboard},
	mMouse{mouse},
	mSurface{surface}
{}

void Scene::Populate()
{
	mMesh = Display::CreateMeshFromObjFile("C:\\dev\\c-excercises\\course6\\toyapp-adam\\test_shapes\\cow.obj");
	mMesh.transform.SetPosition({0.0f, 0.0f, 2.5f});
	mMesh.transform.SetScale(0.3f);
	mMesh.fillColor = Display::GREEN;
}

void Scene::Update(double totalElapsedSeconds)
{
	using Math::Vector3D;

	const float camMovementSpeed = 0.01f;
	const float camRotationSpeed = 0.8f;

	Vector3D cameraMove;

	if(mKeyboard.IsDown(SDL_SCANCODE_LEFT))
		cameraMove[0] = -camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_RIGHT))
		cameraMove[0] = +camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_PAGEUP))
		cameraMove[1] = +camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_PAGEDOWN))
		cameraMove[1] = -camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_DOWN))
		cameraMove[2] = -camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_UP))
		cameraMove[2] = +camMovementSpeed;

	auto camRotation = mMouse.GetPositionDelta();
	mSurface.camera.transform.Move(cameraMove);
	mSurface.camera.transform.Rotate({camRotation[0] * camRotationSpeed, 0.0f, 0.0f});

	mMesh.transform.Rotate({0.01f, 0.0f, 0.0f});
}

void Scene::Draw()
{
	auto view = mSurface.camera.transform.CreateInverseMatrix();

	mSurface.DrawMesh(mMesh, view);
}
