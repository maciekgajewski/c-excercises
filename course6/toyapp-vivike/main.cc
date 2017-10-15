#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/objects.h>

#include <SDL2/SDL_main.h>

#include <iostream>

using namespace Display;

int main(int, char**)
{
	std::cout << "Hello" << std::endl;

	Window win("Hello", 10, 10, 800, 600);
	Surface surf(200, 150);

	Color blue{0, 0, 255};

	surf.Clear(blue); // blue background

	Vector3D corner1({100, 100, 1});
	Vector3D corner2({100, 150, 1});
	Vector3D corner3({150, 150, 1});
	Vector3D corner4({150, 100, 1});
	Rectangle rect{corner1, corner2, corner3, corner4};
	Camera cam;
		

	for(int x = 0; x < 20; x++)
	{
		Color red{255, 0, 0};

		surf.Clear(blue); // blue background
		
		Pixel corner1Proj = cam.project2D(rect.corner1);
		Pixel corner2Proj = cam.project2D(rect.corner2);
		Pixel corner3Proj = cam.project2D(rect.corner3);
		Pixel corner4Proj = cam.project2D(rect.corner4);
		surf.DrawLine(corner1Proj, corner2Proj, red);
		surf.DrawLine(corner2Proj, corner3Proj, red);
		surf.DrawLine(corner3Proj, corner4Proj, red);
		surf.DrawLine(corner4Proj, corner1Proj, red);
		
		win.Display(surf);

		Vector3D moveVec({0, 0, 1});
		rect = rect.move(moveVec);
		
		Delay(200);
	}

	Delay(1000);

	return 0;
}
