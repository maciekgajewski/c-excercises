#include <iostream>
#include <cassert>

class Vector
{
private:
    int mX;
    int mY;

public:
    Vector():mX(0),mY(0){}
    Vector(int x, int y):mX(x), mY(y){}

    Vector operator+(Vector other)const {return Vector(this->mX + other.mX, this->mY + other.mY);}
    bool operator==(Vector other) const {return this->mX == other.mX && this->mY == other.mY;}
    bool operator!=(Vector other) const {return this->mX != other.mX || this->mY != other.mY;}

    int GetX() const
    {
        return mX;
    }

    int GetY() const
    {
        return mY;
    }

    void SetX(int x)
    {
        mX = x;
    }

    void SetY(int y)
    {
        mY = y;
    }

};

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "V[" << v.GetX() << ", " << v.GetY() << "]"<<std::endl;
    return os;
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
