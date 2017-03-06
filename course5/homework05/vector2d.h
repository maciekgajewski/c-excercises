#pragma once
#include <iostream>
#include <string>

namespace vector
{
class Vector2D
{
public:
    enum class System { CARTESIAN, POLAR };

    Vector2D(double initX = 0.0, double initY = 0.0);
    Vector2D(double arg1, double arg2, System system);

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

}

vector::Vector2D operator "" _x(long double initX);
vector::Vector2D operator "" _y(long double initY);

vector::Vector2D operator "" _r(long double initR);
vector::Vector2D operator "" _theta(long double initTheta);

std::ostream& operator<<(std::ostream& s, const vector::Vector2D& vec);
