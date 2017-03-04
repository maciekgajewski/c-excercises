#include "vector2d.h"
#include <cmath>
#include <ostream>

Vector2D::Vector2D(double x, double y): x(x), y(y){}
double Vector2D::GetX() const {return x;}
double Vector2D::GetY() const {return y;}
void Vector2D::SetX(double x){this->x = x;}
void Vector2D::SetY(double y){this->y = y;}
double Vector2D::GetR() const {return sqrt(x*x + y*y);}
double Vector2D::GetPhi() const {return atan(y/x);}

Vector2D Vector2D::operator + (const Vector2D& v)
{
    return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator - (const Vector2D& v)
{
    return Vector2D(this->x - v.x, this->y - v.y);
}

Vector2D Vector2D::operator -()
{
    return Vector2D(-this->x, -this->y);
}

Vector2D Vector2D::operator += (const Vector2D& v)
{
    return *this + v;
}

Vector2D Vector2D::operator -= (const Vector2D& v)
{
    return *this - v;
}

bool Vector2D::operator == (const Vector2D& v)
{
    return this->x == v.x && this->y == v.y;
}

bool Vector2D::operator != (const Vector2D& v)
{
    return !(*this == v);
}

std::ostream& operator << (std::ostream& stream, const Vector2D& v)
{
    stream << "(" << v.GetX() << ", " << v.GetY() << ")";
    return stream;
}
