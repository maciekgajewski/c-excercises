#pragma once

#include <ostream>
#include <math.h>

class Vector2d
{
  int mX;
  int mY;
  Vector2d(int x, int y):mX(x),mY(y) {}

public:
  static Vector2d Rectangular(int x, int y)
  {
      return Vector2d(x,y);
  }

  static Vector2d Polar(double r, double degrees)
  {
      double radians = degrees*M_PI/180;
      int x = r * cos(radians);
      int y = r * sin(radians);
      return Vector2d(x,y);
  }

  Vector2d(){}

  ~Vector2d()
  {}

  void setX(int x)
  {
      mX = x;
  }

  void setY(int y)
  {
      mY = y;
  }

  int getX() const
  {
      return mX;
  }

  int getY() const
  {
      return mY;
  }

  Vector2d operator+(const Vector2d& a)
  {
    Vector2d r(mX + a.getX(), mY + a.getY());
    return r;
  }

  bool operator==(const Vector2d& a)
  {
    return mX == a.getX() && mY == a.getY();
  }
};

  std::ostream& operator<<(std::ostream& ss, const Vector2d& a)
  {
    ss << "(" << a.getX() << ", " << a.getY() << ")";
    return ss;
  }
  

