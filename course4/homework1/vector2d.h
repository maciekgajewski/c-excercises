#pragma once

#include <ostream>

struct Vector2d
{
	double x;
	double y;

	Vector2d(double x, double y) : x(x), y(y) {}
};

Vector2d operator+(const Vector2d& a, const Vector2d& b)
{
	return {a.x + b.x, a.y + b.y};
}

bool operator==(const Vector2d& a, const Vector2d& b)
{
	return (a.x == b.x) && (a.y == b.y);
}

std::ostream& operator<<(std::ostream& os, const Vector2d& obj)
{
	os << "("<< obj.x << ", " << obj.y << ")";
	return os;
}
