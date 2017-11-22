#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/surface3D.h>
#include <displaylib/objects.h>
#include <displaylib/matrix.h>
#include <scene.h>

#include <SDL2/SDL_main.h>

#include <iostream>
#include <vector>

using namespace Display;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <OBJ_FILE>" << std::endl;
		return 1;
	}
	std::cout << "Displaying object loaded from " << argv[1] << "." << std::endl;

	Pixel screenDimensions({1280, 720});

	Window win("Hello", 10, 10, screenDimensions[0], screenDimensions[1]);
	Surface surf(screenDimensions);

	

	Color blue{0, 0, 102};

	surf.Clear(blue); // blue background

	Vector3D corner1({-10.5, -10.5, 0});
	Vector3D corner2({10.5, 10.5, 0});
	Vector3D corner3({-10.5, 10.5, 21});
	Vector3D corner4({10.5, -10.5, 21});
	Triangle triangle1{corner1, corner2, corner3};
	Triangle triangle2{corner1, corner2, corner4};
	Triangle triangle3{corner1, corner3, corner4};
	Triangle triangle4{corner2, corner3, corner4};

	std::vector<Triangle> Pyramid{triangle1, triangle2, triangle3, triangle4};

	Vector3D cameraLocation({0, 0, 0});
	Vector3D cameraOrientation({0, 0, 0});
	Surface3D cam(surf, cameraLocation, cameraOrientation);

	Scene scene(cam);
	scene.LoadMesh(argv[1]);

	Vector3D moveVec({0.0, 0.0, 1.0});

	for(int x = 0; x < 20; x++)
	{
		Color pink{255, 0, 127};

		surf.Clear(blue); // blue background
		
		cam.DrawTriangleVector(Pyramid, pink);
		
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
