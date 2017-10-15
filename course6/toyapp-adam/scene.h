#pragma once

#include <displaylib/mesh.h>
#include <string>

namespace Display {
	class Surface3D;
}

namespace Util {
	class Keyboard;
	class Mouse;
}

using Display::Mesh;
using Display::Surface3D;
using Util::Keyboard;
using Util::Mouse;

class Scene
{
public:
	Scene(Keyboard& keyboard, Mouse& mouse, Surface3D& surface);

	void LoadMesh(const std::string& filePath);
	void Update(double totalElapsedSeconds);
	void Draw();
private:
	Keyboard& mKeyboard;
	Mouse& mMouse;
	Surface3D& mSurface;
	Mesh mMesh;
};
