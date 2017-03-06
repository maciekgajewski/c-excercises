#pragma once

#include <iostream>
#include <cmath>

namespace Course {

class Degree;

class Radian {
    double mRadian;
public:
    explicit Radian(double radian) : mRadian(radian) {}
    Radian(const Degree& degree);

    double Get() const { return mRadian; }
};

class Degree {
    double mDegree;
public:
    explicit Degree(double degree) : mDegree(degree) {}
    Degree(const Radian& radian) : mDegree(radian.Get() * (180.0/M_PI)) {}

    double Get() const { return mDegree; }
};

inline Radian operator"" _rad(long double r) { return Radian(r); }
inline Radian operator"" _rad(unsigned long long r) { return Radian(r); }
inline Degree operator"" _deg(long double d) { return Degree(d); }
inline Degree operator"" _deg(unsigned long long d) { return Degree(d); }

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
    static Vector2D FromPolar(double r, Radian O);

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

Vector2D operator*(Distance r, Radian o);
Course::Distance operator "" _r(long double r);
Course::Distance operator "" _r(unsigned long long r);
Course::Vector2D operator "" _x(long double x);
Course::Vector2D operator "" _y(long double y);
Course::Vector2D operator "" _x(unsigned long long x);
Course::Vector2D operator "" _y(unsigned long long y);

} // namespace

std::ostream& operator<<(std::ostream &os, Course::Vector2D v);
