#pragma once

#include <cstdint>

namespace Display {

struct Color
{
	using Channel = std::uint8_t;

	Channel r;
	Channel g;
	Channel b;

	Color operator*(float intensity)
	{
		return {
			static_cast<Channel>(r * intensity),
			static_cast<Channel>(g * intensity),
			static_cast<Channel>(b * intensity)
		};
	}

	Color operator+(const Color& rhs) const
	{
		return {
			static_cast<Channel>(r + rhs.r),
			static_cast<Channel>(g + rhs.g),
			static_cast<Channel>(b + rhs.b)
		};
	}
};

const Color BLACK{0, 0, 0};
const Color RED{255, 0, 0};
const Color GREEN{0, 255, 0};
const Color BLUE{0, 0, 255};
const Color YELLOW{255, 255, 0};

}
