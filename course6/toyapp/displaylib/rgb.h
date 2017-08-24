#pragma once

#include <cstdint>

namespace Display {

struct Rgb
{
	std::uint8_t r = 0;
	std::uint8_t g = 0;
	std::uint8_t b = 0;
};

constexpr Rgb YELLOW{255, 255, 0};
constexpr Rgb BLUE{0, 0, 128};

}