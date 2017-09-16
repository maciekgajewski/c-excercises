#pragma once

#include <iostream>

namespace Draw {

using VCoord = double;

class Vector3D {
public:
	Vector3D(): x(0),y(0),z(0), w(1) {}
	Vector3D(VCoord x, VCoord y, VCoord z): x(x),y(y),z(z),w(1) {}
	Vector3D(VCoord x, VCoord y, VCoord z, VCoord w): x(x),y(y),z(z),w(w) {}

	VCoord x;
	VCoord y;
	VCoord z;
	VCoord w;

	VCoord& operator[](std::size_t index);
	const VCoord& operator[](std::size_t index) const;

private:

	friend std::ostream& operator<<(std::ostream& s, const Vector3D& v);
};

std::ostream& operator<<(std::ostream& s , const Vector3D& v);
}
