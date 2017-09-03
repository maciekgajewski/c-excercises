#include "vector.h"

namespace Math {

Vector3D Vector3D::operator-() const
{
	return {-x, -y, -z};
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return {x + rhs.x, y + rhs.y, z + rhs.z};
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
	return {x - rhs.x, y - rhs.y, z - rhs.z};
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

}
