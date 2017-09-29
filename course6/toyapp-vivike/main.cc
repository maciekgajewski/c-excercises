#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/objects.h>

#include <SDL2/SDL_main.h>

#include <iostream>


int main(int, char**)
{
	std::cout << "Hello" << std::endl;

	Display::Window win("Hello", 10, 10, 800, 600);
	Display::Surface surf(200, 150);

	Display::Color blue{0, 0, 255};

	surf.Clear(blue); // blue background

	Display::Vector<int, 3> corner1{100, 100, 1};
	Display::Vector<int, 3> corner2{100, 150, 1};
	Display::Vector<int, 3> corner3{150, 150, 1};
	Display::Vector<int, 3> corner4{150, 100, 1};
	Display::Rectangle rect{corner1, corner2, corner3, corner4};
	Display::Camera cam;
		

	for(int x = 0; x < 20; x++)
	{
		Display::Color red{255, 0, 0};

		surf.Clear(blue); // blue background
		
		Display::Vector<int, 2> corner1Proj;
		corner1Proj = cam.project2D(rect.corner1);
		Display::Vector<int, 2> corner2Proj;
		corner2Proj = cam.project2D(rect.corner2);
		Display::Vector<int, 2> corner3Proj;
		corner3Proj = cam.project2D(rect.corner3);
		Display::Vector<int, 2> corner4Proj;
		corner4Proj = cam.project2D(rect.corner4);
		surf.DrawLine(corner1Proj, corner2Proj, red);
		surf.DrawLine(corner2Proj, corner3Proj, red);
		surf.DrawLine(corner3Proj, corner4Proj, red);
		surf.DrawLine(corner4Proj, corner1Proj, red);
		
		win.Display(surf);

		Display::Vector<int, 3> moveVec{0, 0, 1};
		rect = rect.move(moveVec);
		
		Display::Delay(200);
	}

	Display::Delay(1000);

	return 0;
}
