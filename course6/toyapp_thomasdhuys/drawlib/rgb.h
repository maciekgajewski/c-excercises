#pragma once

#include <cstdint>
#include <iostream>

#include "colors.h"

namespace Draw {

struct RGB {
	std::uint8_t r;
	std::uint8_t g;
	std::uint8_t b;
};

namespace Colors {
static const RGB Red{255, 0 , 0};
static const RGB Green{0, 255, 0};
static const RGB Blue{0, 0, 255};
}

std::ostream& operator<<(std::ostream& s, const RGB& rgb); 

}
