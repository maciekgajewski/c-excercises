#include <cstdint>

#include "color.h"

namespace Display {

Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

}
