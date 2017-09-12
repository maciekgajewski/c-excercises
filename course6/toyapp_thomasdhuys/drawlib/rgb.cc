#include "rgb.h"

namespace Draw {

std::ostream& operator<<(std::ostream& s, const RGB& rgb) {
//	if(rgb == Colors::Red)
//		return s << "Red";
//	else if(rgb == Colors::Green)
//		return s << "Green";
//	else if (rgb == Colors::Blue)
//		return s << "Blue";
//	else
		return s << "r" << static_cast<uint16_t>(rgb.r)
                         << "g" << static_cast<uint16_t>(rgb.g)
                         << "b" << static_cast<uint16_t>(rgb.b);
} 

}
