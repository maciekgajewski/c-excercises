#include <iostream>
#include <cassert>

class Vector
{
    // TODO
};

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
