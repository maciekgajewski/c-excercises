#pragma once

#include <cstdint>

namespace Display {

struct Color
{
	using Channel = std::uint8_t;

	Channel r;
	Channel g;
	Channel b;
};

const Color YELLOW{255, 255, 0};
const Color BLUE{0, 0, 128};

}
