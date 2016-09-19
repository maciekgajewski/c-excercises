#pragma once

#include <ostream>

struct Vector2d
{
public:
    Vector2d(int x, int y) : mX(x), mY(y) {}
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
    const int mX;
    const int mY;

    friend std::ostream& operator<<(std::ostream& out, const Vector2d& vector) {
        return out << '(' << vector.mX << ", " << vector.mY << ')';
    }
};
