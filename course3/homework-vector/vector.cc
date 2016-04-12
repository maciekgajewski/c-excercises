#include <iostream>
#include <cassert>

class Vector
{
  public:
    Vector():Vector(0,0)
    {
    }
    Vector(Vector& that) : Vector(that.mX, that.mY)
    {
    }
    Vector(int x, int y) : mX(x), mY(y) 
    {
    }
    int GetX () const
    {
      return mX;
    }
    int GetY() const
    {
      return mY;
    }
    void SetY(int y)
    {
      mY = y;
    }
    void SetX(int x)
    {
      mX = x;
    }

    Vector& operator+(const Vector& that)
    {
      Vector result(mX + that.mX, mY + that.mY);
      return result;
    }

  private:
    int mX;
    int mY;
};

bool operator==(const Vector& lhs, const Vector& rhs)
{
  return lhs.GetX() == rhs.GetX() && lhs.GetY() == rhs.GetY();
}
bool operator!=(const Vector& lhs, const Vector& rhs)
{
  return !(lhs == rhs);
}

int main()
{
    // this all should compile and work
    
    Vector v1;
    Vector v2(5, 6);
    
    assert(v2.GetX() == 5);
    assert(v2.GetY() == 6);
    
    v1 = v2;
    assert(v1.GetX() == 5);
    assert(v1.GetY() == 6);
    assert(v1 == v2);
    
    v1.SetY(7);
    assert(v1.GetY() == 7);
    assert(v1 != v2);
    
    Vector v3 = v1 + v2;
    assert(v3.GetX() == 10);
    assert(v3.GetY() == 13);
    
//    std::cout << v1 << " + " << v2 << " = " << v3 << std::endl;
}
