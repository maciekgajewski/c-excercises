#include "vector2d.h"
#include <cmath>

namespace vector
{

Vector2D::Vector2D(double initX, double initY) : x(initX), y(initY) {}

Vector2D Vector2D::vectorFromPolar(double initR, double initTheta)
{
    return Vector2D::Vector2D(initR * std::cos(initTheta), initR * std::sin(initTheta));
}

double Vector2D::GetX() const { return x; }
double Vector2D::GetY() const { return y; }

void Vector2D::SetX(double newX) { x = newX; }
void Vector2D::SetY(double newY) { y = newY; }

double Vector2D::GetR() const { return std::sqrt(x*x + y*y); }
double Vector2D::GetTheta() const { return std::atan2(y, x); }

std::string Vector2D::AsPolar() const
{
    return "(" + std::to_string(GetR()) + "-r, " + std::to_string(GetTheta()) + "-theta)";
}

Vector2D Vector2D::operator+(const Vector2D& vec) const
{
    return Vector2D(x + vec.x, y + vec.y);
}

Vector2D Vector2D::operator-() const
{
    return Vector2D(-x, -y);
}

Vector2D Vector2D::operator-(const Vector2D& vec) const
{
    return Vector2D(x - vec.x, y - vec.y);
}

void Vector2D::operator+=(const Vector2D& vec)
{
    x = x + vec.x;
    y = y + vec.y;
}

void Vector2D::operator-=(const Vector2D& vec)
{
    x = x - vec.x;
    y = y - vec.y;
}

bool Vector2D::operator==(const Vector2D& vec) const
{
    return (x == vec.x) && (y == vec.y);
}

bool Vector2D::operator!=(const Vector2D& vec) const
{
    return !(*this == vec);
}

Vector2D operator*(const R& r, const Theta& t)
{
    return { r.val * std::cos(t.val), r.val * std::sin(t.val) };
}

Vector2D operator "" _x(long double initX){ return Vector2D(initX, 0.0);}
Vector2D operator "" _y(long double initY){ return Vector2D(0.0, initY);}

R operator "" _r(long double r) { return R{static_cast<double>(r)}; }
Theta operator "" _theta(long double t) { return Theta{static_cast<double>(t)}; }

std::ostream& operator<<(std::ostream& s, const vector::Vector2D& vec)
{
	s << "(" << vec.GetX() << ", " << vec.GetY() << ")";
	return s;
}
} // namespace
