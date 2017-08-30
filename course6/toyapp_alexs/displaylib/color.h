#pragma once

#include <cstdint>

namespace Display {

struct Color {
    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b);

    std::uint8_t r, g, b;
};

}
