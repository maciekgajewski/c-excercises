#pragma once

#include <cmath>
#include <ostream>

struct Vector2d
{
public:
    // named ctors
    static Vector2d fromCarthesian(const double x, const double y) {
        return { x, y };
    }
    static Vector2d fromPolar(const double rho, const double phi) {
        return { rho * cos(phi), rho * sin(phi) };
    }
    // ctor
    Vector2d(double x, double y) : mX(x), mY(y) {}
    // setters
    void X(const double x) {
        mX = x; 
    }
    void Y(const double y) {
        mY = y;
    }
    // getters 
    double X() const {
        return mX;
    }
    double Y() const {
        return mY;
    }
    double Rho() const {
        return sqrt(mX*mX + mY*mY);
    }
    double Phi() const {
        return atan2(mY, mX);
    }
    // operators
    bool operator==(const Vector2d& other) const {
        return mX == other.mX && mY == other.mY;
    }
    Vector2d operator+(const Vector2d& other) const {
        return { mX + other.mX, mY + other.mY };
    }
    Vector2d operator-(const Vector2d& other) const {
        return { mX - other.mX, mY - other.mY };
    }
private:
    double mX;
    double mY;

    friend std::ostream& operator<<(std::ostream& out, const Vector2d& vector) {
        return out << '(' << vector.mX << ", " << vector.mY << ')';
    }
};
