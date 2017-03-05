
#include "vector2d.h"

#include <cmath>

namespace Vector {

double Vector2D::GetRad() const
{
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

double Vector2D::GetTheta() const
{
	return std::atan(y / x);
}

bool Vector2D::operator==(const Vector2D& lhs) const
{
	return x == lhs.x && y == lhs.y;
}

bool Vector2D::operator!=(const Vector2D& lhs) const
{
	return !(*this == lhs);
}

Vector2D Vector2D::operator+(const Vector2D& lhs)
{
	return { x + lhs.x, y + lhs.y };
}

Vector2D& Vector2D::operator+=(const Vector2D& lhs)
{
	x += lhs.x;
	y += lhs.y;
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D& lhs)
{
	return { x - lhs.x, y - lhs.y };
}

Vector2D& Vector2D::operator-=(const Vector2D& lhs)
{
	x -= lhs.x;
	y -= lhs.y;
	return *this;
}

Vector2D operator+(const RadialCoord& r, const AngularCoord& t)
{
	return { r.val * std::cos(t.val), r.val * std::sin(t.val) };
}

Vector2D operator+(const AngularCoord& t, const RadialCoord& r)
{
	return r + t;
}


}
