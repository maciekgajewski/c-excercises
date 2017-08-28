#include "vector2d.h"

namespace homework{

    Polar::Polar(double rr, double tt)
    {
        r = rr;
        theta = tt;
    }

    Polar Polar::operator+(const Polar& src) const
    {
        return Polar(r+src.r, theta+src.theta);
    }


    Polar operator "" _r (long double rr)
    {
        return Polar(rr, 0);
    }

    Polar operator "" _theta (long double tt)
    {
        return Polar(0, tt);
    }




    Vector2D::Vector2D(double xx, double yy): x(xx), y(yy)
    {

    }

    Vector2D::Vector2D(const Vector2D& src)
    {
        x = src.x;
        y = src.y;
    }

    Vector2D::Vector2D(const Polar& src)
    {
        x = src.GetR() * std::cos(src.GetTheta());
        y = src.GetR() * std::sin(src.GetTheta());
    }

    Vector2D& Vector2D::operator=(const Vector2D& src)
    {
        x = src.x;
        y = src.y;
        return *this;
    }

    Vector2D Vector2D::operator+(const Vector2D& src) const
    {
        return Vector2D(x+src.x, y+src.y);
    }

    Vector2D Vector2D::operator-(const Vector2D& src) const
    {
        return Vector2D(x-src.x, y-src.y);
    }

    Vector2D Vector2D::operator-()
    {
        return Vector2D(-x, -y);
    }

    Vector2D& Vector2D::operator+=(const Vector2D& src)
    {
        x += src.x;
        y += src.y;
        return *this;
    }

    Vector2D& Vector2D::operator-=(const Vector2D& src)
    {
        x -= src.x;
        y -= src.y;
        return *this;
    }

    bool Vector2D::operator==(Vector2D src)
    {
        return x==src.x && y==src.y;
    }

    bool Vector2D::operator!=(Vector2D src)
    {
        return x!=src.x || y!=src.y;
    }




    Vector2D operator "" _x (long double xx)
    {
        return Vector2D(xx,0);
    }

    Vector2D operator "" _y (long double yy)
    {
        return Vector2D(0,yy);
}

}

std::ostream& operator<< (std::ostream& s, const homework::Vector2D vector)
{
    std::cout << "vector is: " << '(' << vector.GetX() << ',' << vector.GetY() << ')' << std::endl;
    return s;
}
