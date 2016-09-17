#pragma once

#include <ostream>
#include <sstream>


struct Vector2d
{
  int X;
  int Y;
  Vector2d operator+(const Vector2d& a)
  {
    Vector2d r;
    r.X = X + a.X;
    r.Y = Y + a.Y;
    return r;
  }
  
  bool operator==(const Vector2d& a)
  {
    return X == a.X and Y == a.Y;
  }
};

  std::ostream& operator<<(std::ostream& ss, const Vector2d& a)
  {
    ss << "(" << a.X << ", " << a.Y << ")";
    return ss;
  }
  

