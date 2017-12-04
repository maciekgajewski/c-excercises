#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>
#include <displaylib/surface3D.h>
#include <displaylib/objects.h>
#include <displaylib/matrix.h>
#include <scene.h>

#include <util/clock.h>

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

	SDL_Init( SDL_INIT_EVERYTHING );

	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	auto width = DM.w;
	auto height = DM.h;
	Pixel screenDimensions({width, height});

	Util::Clock clock;

	Window win("Hello", 100, 100, screenDimensions[0], screenDimensions[1]);
	SDL_SetWindowFullscreen(win.getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);

	Surface surf(screenDimensions);

	Vector3D cameraLocation({0, 0, 0});
	Vector3D cameraOrientation({0, 0, 0});
	Surface3D cam(surf, cameraLocation, cameraOrientation);

	Color blue{0, 0, 102};
	surf.Clear(blue); // blue background

	Scene scene(cam);
	scene.LoadMesh(argv[1]);

	Vector3D moveVec({0.0, 0.0, 1.0});

	SDL_SetRelativeMouseMode(SDL_TRUE);

	for(int x = 0; x < 20; x++)
	{
		// Color pink{255, 0, 127};

		scene.Update(clock.GetTotalElapsedSeconds());

		surf.Clear(blue); // blue background
		scene.Draw();
		win.Display(surf);
		
		cam.Rotate(moveVec);
		
		Delay(100);
	}

	Delay(1000);

	return 0;
}
