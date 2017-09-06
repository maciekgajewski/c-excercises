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

const Color BLACK{0, 0, 0};
const Color RED{255, 0, 0};
const Color GREEN{0, 255, 0};
const Color BLUE{0, 0, 255};
const Color YELLOW{255, 255, 0};

}
