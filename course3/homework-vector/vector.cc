#include <iostream>
#include <cassert>

class Vector
{
private:
    double mX = 0;
    double mY = 0;

public:
    Vector() = default;

    Vector(double x, double y): mX(x), mY(y) {}

    double GetX() const { return mX; }

    double GetY() const { return mY; }

    void SetX(double x) { mX = x; }

    void SetY(double y) { mY = y; }

    bool operator==(const Vector& vec) const
    {
        return mX == vec.mX && mY == vec.mY;
    }

    bool operator!=(const Vector& vec) const
    {
        return !operator==(vec);
    }

    Vector operator+(const Vector& vec) const // is it okay to return by value here?
    {
        return Vector(mX + vec.mX, mY + vec.mY);
    }
};

std::ostream& operator<<(std::ostream &out, const Vector& vec)
{
    out << "(" << vec.GetX() << "," << vec.GetY() << ")";
    return out;
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
    
    std::cout << v1 << " + " << v2 << " = " << v3 << std::endl;
}
