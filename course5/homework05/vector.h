#pragma once

#include <iostream>
#include <cmath>

namespace Course {

class Angle {
    double mRadian;
public:
    static Angle FromRadian(double radian) { return Angle(radian); }
    static Angle FromDegree(double degree) { return Angle(degree * (180.0/M_PI)); }

    double GetRadian() const { return mRadian; }
private:
    explicit Angle(double radian) : mRadian(radian) {}
};

inline Angle operator"" _rad(long double r) { return Angle::FromRadian(r); }
inline Angle operator"" _rad(unsigned long long r) { return Angle::FromRadian(r); }
inline Angle operator"" _deg(long double d) { return Angle::FromDegree(d); }
inline Angle operator"" _deg(unsigned long long d) { return Angle::FromDegree(d); }

class Distance
{
public:
    explicit Distance(double r)
        : mR(r)
    {}

    double Get() { return mR; }
private:
    double mR;
};

class Vector2D
{
public:
    Vector2D(double x, double y);
    Vector2D(Vector2D const &) = default;
    Vector2D(Vector2D &&) = default;
    Vector2D& operator=(Vector2D const &) = delete;
    Vector2D& operator=(Vector2D &&rhs) = default;

    // vector small enough that it likely better to take as value
    bool operator==(Vector2D rhs);
    bool operator!=(Vector2D rhs);
    Vector2D operator-();
    Vector2D operator+(Vector2D rhs);
    Vector2D operator-(Vector2D rhs);
    Vector2D& operator+=(Vector2D rhs);
    Vector2D& operator-=(Vector2D rhs);
    static Vector2D FromPolar(double r, Angle O);

    double GetX() const { return mX; }
    double GetY() const { return mY; }

    // Getters for polar coordinates
    double GetR() const { return std::sqrt(mX*mX + mY*mY); }
    double GetO() const { return std::atan2(mY, mX); }

    void SetX(double x) { mX = x; }
    void SetY(double y) { mY = y; }
private:
    double mX, mY;
};

Vector2D operator*(Distance r, Angle o);
Course::Distance operator "" _r(long double r);
Course::Distance operator "" _r(unsigned long long r);
Course::Vector2D operator "" _x(long double x);
Course::Vector2D operator "" _y(long double y);
Course::Vector2D operator "" _x(unsigned long long x);
Course::Vector2D operator "" _y(unsigned long long y);

} // namespace

std::ostream& operator<<(std::ostream &os, Course::Vector2D v);
