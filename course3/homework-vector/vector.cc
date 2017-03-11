#include <iostream>
#include <cassert>
#include <cmath>

class Vector
{
    int mX, mY;

public:
    Vector() {}
    Vector(int x, int y) : mX(x), mY(y) {}

    int GetX() const { return mX; }
    int GetY() const { return mY; }

    double GetPolarLength() const { return sqrt((mX * mX) + (mY * mY)); }
    double GetPolarAngle() const { return atan2(mX, mY); }

    void SetX(int x) { mX = x; }
    void SetY(int y) { mY = y; }

    bool operator==(const Vector& rhs) {
        return ((rhs.GetX() == this->GetX()) && (rhs.GetY() == this->GetY()));
    }

    bool operator!=(const Vector& rhs) {
        return !((rhs.GetX() == this->GetX()) && (rhs.GetY() == this->GetY()));
    }

    Vector operator+(const Vector& rhs) {
        int sumX = this->GetX() + rhs.GetX();
        int sumY = this->GetY() + rhs.GetY();

        return Vector(sumX, sumY);
    }
};

std::ostream& operator<<(std::ostream& out, const Vector& vec) {
    return out << "{x= " << vec.GetX() << " , y= " << vec.GetY() << "}" << std::endl;
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
    
    std::cout << "polar length: " << v1.GetPolarLength() << " angle: " << v1.GetPolarAngle() << std::endl;
    std::cout << v1 << " + " << v2 << " = " << v3 << std::endl;
}
