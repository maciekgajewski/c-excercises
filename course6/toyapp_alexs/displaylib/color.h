#pragma once

#include <cstdint>

namespace Display {

struct Color {
	std::uint8_t r, g, b;
};

const Display::Color BLUE {0, 0, 255};
const Display::Color RED {255, 0, 0};

}
