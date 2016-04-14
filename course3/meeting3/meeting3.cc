#include <iostream>

class Vector
{
private:
    int mX = 0;
    int mY = 0;
    
public:
    Vector() = default;
    Vector(int x, int y) : mX(x), mY(y) {}
    
    int GetX() const { return mX; }
    int GetY() const { return mY; }
    void SetX(int x) { mX = x; }
    
};

std::ostream& operator<<(std::ostream& o, const Vector& v)
{
    return o << v.GetX() << ", " << v.GetY();
}
Vector operator+(const Vector& a, const Vector& o)
{
    return Vector(a.GetX()+o.GetX(), a.GetY()+o.GetY());
}

int main()
{
    Vector v1(3, 66);
    Vector v2(6, 7);
    std::cout << (v1 + v2) << std::endl;
}

