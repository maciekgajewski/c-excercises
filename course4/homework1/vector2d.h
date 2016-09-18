#pragma once

#include <ostream>

struct Vector2d
{
private:
   double mX, mY;

public:

   Vector2d(const double& x, const double& y)
   {
     mX = x;
     mY = y;
   }

   double GetX() const
   {
       return mX;
   }

   double GetY() const
   {
       return mY;
   }
};

std::ostream& operator<<(std::ostream& os, const Vector2d& target)
{
   os << "(" << target.GetX() << ", " << target.GetY() <<")";
   return os;
}

bool operator == (const Vector2d& right, const Vector2d& left)
{
    return right.GetX() == left.GetX() && right.GetY() == left.GetY();
}

Vector2d operator +(const Vector2d& right, const Vector2d& left)
{
    return Vector2d(right.GetX() + left.GetX(), right.GetY() + left.GetY());
}

