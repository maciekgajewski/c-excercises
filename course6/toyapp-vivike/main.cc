#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/surface3D.h>
#include <displaylib/objects.h>
#include <displaylib/matrix.h>

#include <SDL2/SDL_main.h>

#include <iostream>
#include <vector>

using namespace Display;

int main(int, char**)
{
	std::cout << "Hello" << std::endl;

	Window win("Hello", 10, 10, 800, 600);
	Surface surf(200, 150);

	Color blue{0, 0, 255};

	surf.Clear(blue); // blue background

	Vector3D corner1({-0.5, -0.5, -0.5});
	Vector3D corner2({0.5, 0.5, -0.5});
	Vector3D corner3({-0.5, 0.5, 0.5});
	Vector3D corner4({0.5, -0.5, 0.5});
	Triangle triangle1{corner1, corner2, corner3};
	Triangle triangle2{corner1, corner2, corner4};
	Triangle triangle3{corner1, corner3, corner4};
	Triangle triangle4{corner2, corner3, corner4};

	std::vector<Triangle> Pyramid{triangle1, triangle2, triangle3, triangle4};

	Vector3D cameraLocation({0, 0, 0});
	Vector3D cameraOrientation({0, 0, 0});
	Surface3D cam(surf, cameraLocation, cameraOrientation);

	Vector3D moveVec({0.0, 0.0, 1.0});

	for(int x = 0; x < 20; x++)
	{
		Color red{255, 0, 0};

		surf.Clear(blue); // blue background
		
		cam.DrawTriangleVector(Pyramid, red);
		
		win.Display(surf);

		for (Triangle& tri : Pyramid)
		{
			tri.move(moveVec);
		}
		
		Delay(100);
	}

	Delay(1000);

	return 0;
}
