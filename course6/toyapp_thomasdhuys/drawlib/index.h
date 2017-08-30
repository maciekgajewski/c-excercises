#pragma once

#include <cstdint>

#include "rgb.h"
#include "colors.h"

namespace Draw {

struct Index {
	Index(): x(0), y(0), z(0), color(Draw::Colors::Red) {}
	std::uint8_t x;
	std::uint8_t y;
	std::uint8_t z;
	rgb color;

	std::string ToString() { return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z)+")";}
};

}
