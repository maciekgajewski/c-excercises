#include "vector.h"

namespace Course {

Vector2D::Vector2D(double x, double y) : mX(x), mY(y)
{}

bool Vector2D::operator==(Vector2D rhs)
{
    return mX == rhs.mX && mY == rhs.mY;
}

bool Vector2D::operator!=(Vector2D rhs)
{
    return !(*this == rhs);
}

Vector2D Vector2D::operator-()
{
    return Vector2D(-mX, -mY);
}

Vector2D Vector2D::operator+(Vector2D rhs)
{
    return Vector2D(mX+rhs.mX, mY+rhs.mY);
}

Vector2D Vector2D::operator-(Vector2D rhs)
{
    return Vector2D(mX-rhs.mX, mY-rhs.mY);
}

Vector2D& Vector2D::operator+=(Vector2D rhs)
{
    mX += rhs.mX;
    mY += rhs.mY;
    return *this;
}

Vector2D& Vector2D::operator-=(Vector2D rhs)
{
    mX += rhs.mX;
    mY += rhs.mY;
    return *this;
}

Vector2D operator*(Distance r, Angle o)
{
    return Vector2D::FromPolar(r.Get(), o);
}

Vector2D Vector2D::FromPolar(double r, Angle O)
{
    return Vector2D(r * std::cos(O.GetRadian()), r * std::sin(O.GetRadian()));
}

Distance operator "" _r(long double r)
{
    return Course::Distance(r);
}

Distance operator "" _r(unsigned long long r)
{
    return Course::Distance(r);
}

Vector2D operator "" _x(long double x)
{
    return Course::Vector2D(x, 0);
}

Vector2D operator "" _y(long double y)
{
    return Course::Vector2D(0, y);
}

Vector2D operator "" _x(unsigned long long x)
{
    return Course::Vector2D(x, 0);
}

Vector2D operator "" _y(unsigned long long y)
{
    return Course::Vector2D(0, y);
}

}

std::ostream& operator<<(std::ostream &os, Course::Vector2D v)
{
    std::cout << '(' << v.GetX() << ", " << v.GetY() << ')';
    return os;
}
