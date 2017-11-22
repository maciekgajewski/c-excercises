#include "scene.h"

#include <displaylib/mesh_util.h>
#include <displaylib/mesh.h>
#include <displaylib/surface3D.h>


Scene::Scene(Surface3D& surface) : mSurface{surface} {}

void Scene::LoadMesh(const std::string& filePath)
{
	mMesh = Display::CreateMeshFromObjFile(filePath);
	mMesh.NormalizeScale();
	Display::Vector3D position({0.0f, 0.0f, 1.5f});
	mMesh.transform.SetPosition(position); // hardcoded for now
	mMesh.fillColor = Display::GREEN;
}

void Scene::Update(double totalElapsedSeconds)
{
	const float camRotationSpeed = 0.8f;

	Display::Vector3D camRotation({1 * camRotationSpeed, 0.0f, 0.0f});
	mSurface.Rotate(camRotation);

	Display::Vector3D meshRotation({0.01f, 1 * camRotationSpeed , 0.0f});
	mMesh.transform.Rotate(meshRotation);
}

void Scene::Draw()
{
	auto view = mSurface.createInverseMatrix();

	mSurface.DrawMesh(mMesh, view);
}