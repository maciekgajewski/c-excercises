#include <iostream>
#include <cmath>
#include "vector2d.h"

using namespace jds;

namespace jds {
        Vector2D::Vector2D(double x, double y)
        {
                this->x = x;
                this->y = y;
        }

        Vector2D Vector2D::Polar(double r, double t)
        {
                auto x = r * std::cos(t);
                auto y = r * std::sin(t);
                return Vector2D(x, y);
        }

        double Vector2D::GetX() const
        {
                return x;
        }

        double Vector2D::GetY() const
        {
                return y;
        }

        double Vector2D::GetR() const
        {
                return std::sqrt(x*x + y*y);
        }

        double Vector2D::GetPhi() const
        {
                return std::atan2(y, x);
        }

        Vector2D Vector2D::operator+(const Vector2D& that) const
        {
                return Vector2D(x + that.x, y + that.y);
        }

        Vector2D Vector2D::operator-() const
        {
                return Vector2D(-x, -y);
        }

        Vector2D Vector2D::operator-(const Vector2D& that) const
        {
                return Vector2D(x - that.x, y - that.y);
        }

        Vector2D& Vector2D::operator+=(const Vector2D& that)
        {
                x += that.x;
                y += that.y;
                return *this;
        }

        Vector2D& Vector2D::operator-=(const Vector2D& that)
        {
                x -= that.x;
                y -= that.y;
                return *this;
        }

        bool Vector2D::operator==(const Vector2D& that) const
        {
                return x == that.x && y == that.y;
        }
}

std::ostream& operator<<(std::ostream& s, const Vector2D& v)
{
        s << '(' << v.GetX() << ',' << v.GetY() << ')';
        return s;
}

Vector2D operator "" _x(long double x) { return Vector2D(x, 0); }
Vector2D operator "" _y(long double y) { return Vector2D(0, y); }
Vector2D operator "" _r(long double r) { return Vector2D::Polar(r, 0); }
Vector2D operator "" _t(long double t) { return Vector2D::Polar(0, t); }
