#include "color.h"

namespace Draw {

std::ostream& operator<<(std::ostream& s, const Color& color) {
//	if(color == Colors::Red)
//		return s << "Red";
//	else if(color == Colors::Green)
//		return s << "Green";
//	else if (color == Colors::Blue)
//		return s << "Blue";
//	else
		return s << "r" << static_cast<uint16_t>(color.r)
                         << "g" << static_cast<uint16_t>(color.g)
                         << "b" << static_cast<uint16_t>(color.b);
} 

}
