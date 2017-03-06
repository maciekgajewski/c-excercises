#include "vector2d.h"
#include <cmath>

using namespace vector;

Vector2D::Vector2D(double initX, double initY) : x(initX), y(initY) {}

Vector2D::Vector2D(double arg1, double arg2, System system)
{
    double initX;
    double initY;
    switch(system)
    {
    case System::POLAR:
        initX = arg1 * std::cos(arg2);
        initY = arg1 * std::sin(arg2);
        break;
    case System::CARTESIAN:
        initX = arg1;
        initY = arg2;
        break;
    }
    x = initX;
    y = initY;
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

Vector2D operator "" _x(long double initX){ return Vector2D(initX, 0.0);}
Vector2D operator "" _y(long double initY){ return Vector2D(0.0, initY);}

Vector2D operator "" _r(long double initR){ return Vector2D(initR, 0.0, Vector2D::System::POLAR);}
Vector2D operator "" _theta(long double initTheta){ return Vector2D(std::cos(0.0), initTheta, Vector2D::System::POLAR);}

std::ostream& operator<<(std::ostream& s, const vector::Vector2D& vec)
{
	s << "(" << vec.GetX() << ", " << vec.GetY() << ")";
	return s;
}
