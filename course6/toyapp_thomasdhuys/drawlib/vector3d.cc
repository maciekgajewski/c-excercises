#include "vector3d.h"

#include <stdexcept>

namespace Draw {

std::ostream& operator<<(std::ostream& s , const Vector3D& v)
{
	return s << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")" ;
}

VCoord& Vector3D::operator[](std::size_t index)
{
	switch(index) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw std::out_of_range ("Index must be < 4");
	}
}

const VCoord& Vector3D::operator[](std::size_t index) const
{
	switch(index) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw std::out_of_range ("Index must be < 4");
	}
}

}
