#pragma once

#include <iostream>
#include <cstdint>
#include <memory>

#include "rgb.h"
#include "colors.h"

namespace Draw {

struct Index;
using XCoord = int;
using IndexP = std::shared_ptr<Index>;

// Treat Index as a memory intensive object
struct Index {
	Index(): x(0), y(0), z(0), color(Draw::Colors::Red) {}
	Index(XCoord x, XCoord y, XCoord z): x(x), y(y), z(z), color(Draw::Colors::Red) {}
	Index(XCoord x, XCoord y, XCoord z, RGB color): x(x), y(y), z(z), color(color) {}
	~Index() { std::cout << "Idx Destructed: " << ToString() << std::endl; }

	XCoord x;
	XCoord y;
	XCoord z;

	RGB color;

	std::string ToString() { return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z)+")"; }
	void Print() { std::cout << "Idx" << ToString() << std::endl; }
};

}
