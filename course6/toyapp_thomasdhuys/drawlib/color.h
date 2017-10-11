#pragma once

#include <cstdint>
#include <iostream>

namespace Draw {

struct Color {
	std::uint8_t r;
	std::uint8_t g;
	std::uint8_t b;
};

namespace Colors {
static const Color Red{255, 0 , 0};
static const Color Green{0, 255, 0};
static const Color Blue{0, 0, 255};
}

std::ostream& operator<<(std::ostream& s, const Color& color); 

}
