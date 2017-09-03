#include "vector.h"

#include "surface.h"

namespace Display {

void Vector3D::Draw(Surface3D& surface, Color color) const
{
	surface.SetPixel(*this, color);
}

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
