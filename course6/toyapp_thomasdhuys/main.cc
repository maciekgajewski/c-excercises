#include <iostream>
#include <memory>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>

#include <drawlib/renderer.h>
#include <drawlib/scene.h>
#include <drawlib/primitives.h>
#include <drawlib/vertex.h>
#include <drawlib/vector3d.h>
#include <drawlib/matrix.h>

int main()
{
	std::cout << "Hello, here I am!" << std::endl;

	int surfaceWidth = 200;
	int surfaceHeight = 150;

	auto renderer = Draw::Renderer(surfaceWidth, surfaceHeight);
	auto scenes = Draw::SceneFactory::GetScenes();

	renderer.Render(scenes);
	
	// Test
	Draw::Matrix4x4 m;

	m.Set(3,1,3);

	std::cout << m.Get(1,3) << std::endl;
	std::cout << m.Get(3,1) << std::endl;

	return 0;
}
