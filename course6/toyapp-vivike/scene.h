#pragma once

#include <displaylib/mesh.h>
#include <string>

namespace Display {
	class Surface3D;
}

using Display::Mesh;
using Display::Surface3D;

class Scene
{
public:
	Scene(Surface3D& surface);

	void LoadMesh(const std::string& filePath);
	void Update(double totalElapsedSeconds);
	void Draw();
private:
	Surface3D& mSurface;
	Mesh mMesh;
};