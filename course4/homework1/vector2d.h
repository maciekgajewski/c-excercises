#pragma once

#include <math.h>
#include <ostream>

struct Vector2d
{
private:
   double mX, mY;

public:

   Vector2d(const double x, const double y):
       mX(x), mY(y)
   {
   }

   static Vector2d createByPolarCoordinates(double rho, double phi)
   {
      return Vector2d(rho * cos(phi), rho * sin(phi));
   }

   double GetX() const
   {
       return mX;
   }

   void SetX(const double x)
   {
       mX = x;
   }

   void SetY(const double y)
   {
       mY = y;
   }

   double GetY() const
   {
       return mY;
   }

   double GetRho() const
   {
       return sqrt(pow(mX, 2) + pow(mY, 2));
   }

   double GetPhi() const
   {
       return atan2(mY, mX);
   }

   bool operator == (const Vector2d& other) const
   {
       return other.mX == mX && other.mY == mY;
   }

   Vector2d operator +(const Vector2d& other) const
   {
       return Vector2d(mX + other.mX, mY + other.mY);
   }
};

std::ostream& operator<<(std::ostream& os, const Vector2d& target)
{
   os << "(" << target.GetX() << ", " << target.GetY() <<")";
   return os;
}



