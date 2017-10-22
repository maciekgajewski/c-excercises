#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/surface3D.h>
#include <displaylib/objects.h>
#include <displaylib/matrix.h>

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

	Vector3D center({0, 0, 1.0});
	Vector3D orientation({0, 0, 0});
	Square square{1.6, center, orientation};

	Vector3D cameraLocation({0, 0, 0});
	Surface3D cam(surf, cameraLocation);

	for(int x = 0; x < 20; x++)
	{
		Color red{255, 0, 0};

		surf.Clear(blue); // blue background
		
		for(auto line : square.edges())
		{
			cam.DrawLine(line[0], line[1], red);
		}
		
		win.Display(surf);

		Vector3D moveVec({0.0, 0.0, 1.0});
		square.move(moveVec);
		
		Delay(100);
	}

	Delay(1000);

	return 0;
}
