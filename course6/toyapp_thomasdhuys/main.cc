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

using namespace Draw;

void test();

int main()
{
	std::cout << "Hello, here I am!" << std::endl;

	auto renderer = Draw::Renderer();
	auto scenes = Draw::SceneFactory::GetScenes();

	renderer.Render(scenes);

    //test();

	return 0;
}

void test()
{
    // Test
    Vector3D v = {1,2,3};
	Matrix4x4 m = Matrix4x4::Scale(0.5);

    std::cout << "V=" << v << std::endl;
    std::cout << "M=" << m << std::endl;

    v = m * v;
    std::cout << "V=" << v << std::endl;

	m[1][3] = 3;

	std::cout << m[1][3] << std::endl;
	std::cout << m[3][1] << std::endl;
}
