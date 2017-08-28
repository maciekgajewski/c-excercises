#pragma once

#include <ostream>

#include <iostream>

namespace Vector {

class Vector2D
{
public:
	Vector2D() = default;
	Vector2D(double x, double y) : x(x), y(y) { }

	double GetX() const { return x; };
	double GetY() const { return y; };
	void SetX(double x) { this->x = x; }
	void SetY(double y) { this->y = y; }

	// Getters for the radial components
	double GetRad() const;
	double GetTheta() const;

	bool operator==(const Vector2D& lhs) const;
	bool operator!=(const Vector2D& lhs) const;
	Vector2D operator+(const Vector2D& lhs);
	Vector2D& operator+=(const Vector2D& lhs);
	Vector2D operator-(const Vector2D& lhs);
	Vector2D& operator-=(const Vector2D& lhs);

private:
	double x = 0.0;
	double y = 0.0;
};

struct RadialCoord { double val; };
struct AngularCoord { double val; };

inline Vector2D operator "" _x(long double x) { return Vector2D(x, 0.0); }
inline Vector2D operator "" _y(long double y) { return Vector2D(0.0, y); }
inline RadialCoord operator "" _r(long double r) { return RadialCoord{static_cast<double>(r)}; }
inline AngularCoord operator "" _t(long double t) { return AngularCoord{static_cast<double>(t)}; }

Vector2D operator-(const Vector2D& v);
Vector2D operator*(const RadialCoord& r, const AngularCoord& t);
Vector2D operator*(const AngularCoord& t, const RadialCoord& r);

inline std::ostream& operator<<(std::ostream& s, const Vector2D& v)
{
	s << "(x: " << v.GetX() << ", y: " << v.GetY() << ")";
	return s;
}

}
