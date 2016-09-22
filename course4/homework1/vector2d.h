#pragma once

#include <ostream>

struct Vector2d
{
	// TODO
private:
	double x;
	double y;
public:
	Vector2d() = delete;
	Vector2d(double a, double b) : x(a), y(b) {}
	Vector2d operator+ (const Vector2d& v2) 
	{
		return{ x + v2.x, y + v2.y };
	};
	bool operator== (const Vector2d& v2)
	{
		return (x == v2.x) && (y == v2.y) ? true : false;
	}
	friend std::ostream& operator<< (std::ostream& os, const Vector2d& v) 
	{
		os << "(" << v.x << ", " << v.y << ")";
		return os;
	}
};
