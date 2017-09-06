#pragma once

#include <iostream>

namespace Draw {

using VCoord = double;

class Vector3D {
public:
	Vector3D(): x(0),y(0),z(0) {}
	Vector3D(VCoord x, VCoord y, VCoord z): x(x),y(y),z(z) {}

	VCoord x;
	VCoord y;
	VCoord z;
private:

	friend std::ostream& operator<<(std::ostream& s, const Vector3D& v);
};

std::ostream& operator<<(std::ostream& s , const Vector3D& v);
}
