#pragma once
#include <iostream>
#include <string>

namespace vector
{

struct R { double val; };
struct Theta { double val; };

class Vector2D
{
public:
    Vector2D(double initX = 0.0, double initY = 0.0);
    static Vector2D vectorFromPolar(double initR, double initTheta);

    double GetX() const;
    double GetY() const;

    void SetX(double newX);
    void SetY(double newY);

    double GetR() const;
    double GetTheta() const;

    std::string AsPolar() const;

    Vector2D operator+(const Vector2D& vec) const;
    Vector2D operator-() const;
    Vector2D operator-(const Vector2D& vec) const;
    void operator+=(const Vector2D& vec);
    void operator-=(const Vector2D& vec);
    bool operator==(const Vector2D& vec) const;
    bool operator!=(const Vector2D& vec) const;

private:
    double x;
    double y;
};
Vector2D operator*(const R& r, const Theta& t);

Vector2D operator "" _x(long double initX);
Vector2D operator "" _y(long double initY);

R operator "" _r(long double r);
Theta operator "" _theta(long double t);

std::ostream& operator<<(std::ostream& s, const Vector2D& vec);
}
