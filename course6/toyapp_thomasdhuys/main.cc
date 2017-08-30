#include <iostream>
#include <memory>

#include <displaylib/window.h>
#include <displaylib/functions.h>
#include <displaylib/surface.h>

#include <drawlib/primitives.h>
#include <drawlib/index.h>

int main()
{
	std::cout << "Hello, here I am!" << std::endl;


	auto idx0 = std::make_unique<Draw::Index>();
	Draw::Primitives::Point 	point(idx0.get());
	Draw::Primitives::Line 		line(idx0.get(), idx0.get());
	Draw::Primitives::Triangle 	triangle(idx0.get(), idx0.get(), idx0.get());

	std::cout << point.ToString() << std::endl;
	std::cout << line.ToString() << std::endl;
	std::cout << triangle.ToString() << std::endl;

	for(int x = 0; x < 100; x++)
	{
//		surf.Clear(0, 0, 255); // blue background
//		surf.SetPixel(10+x, 10, 255, 0, 0); // red pixel at 10x10
//		win.Display(surf);
//		Display::Delay(50);
	}

//	Display::Delay(1000);

	return 0;
}
