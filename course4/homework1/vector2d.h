#pragma once

#include <cmath>
#include <ostream>

struct Vector2d
{
public:
    // named ctors
    static Vector2d fromCarthesian(double x, double y) {
        return { x, y };
    }
    static Vector2d fromPolar(double rho, double phi) {
        return { rho * std::cos(phi), rho * std::sin(phi) };
    }
    // setters
    void X(double x) {
        mX = x; 
    }
    void Y(double y) {
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
        return std::sqrt(mX*mX + mY*mY);
    }
    double Phi() const {
        return std::atan2(mY, mX);
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

    Vector2d(double x, double y) : mX(x), mY(y) {}

    friend std::ostream& operator<<(std::ostream& out, const Vector2d& vector) {
        return out << '(' << vector.mX << ", " << vector.mY << ')';
    }
};
