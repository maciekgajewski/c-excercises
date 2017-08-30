#pragma once

#include <iostream>
#include <cstdint>

#include "rgb.h"
#include "colors.h"

namespace Draw {

using XCoord = int;

struct Index {
	Index(): x(0), y(0), z(0), color(Draw::Colors::Red) {}
	Index(XCoord x, XCoord y, XCoord z): x(x), y(y), z(z), color(Draw::Colors::Red) {}
	Index(XCoord x, XCoord y, XCoord z, rgb color): x(x), y(y), z(z), color(color) {}
	~Index() { std::cout << "Idx Destructed: " << ToString() << std::endl; }

	XCoord x;
	XCoord y;
	XCoord z;

	rgb color;

	std::string ToString() { return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z)+")"; }
	void Print() { std::cout << "Idx" << ToString() << std::endl; }
};

}
