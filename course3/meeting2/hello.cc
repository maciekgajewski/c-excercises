#include <iostream>
#include <cstdint>

struct Vector
{
    Vector() { std::cout << "Vector(this="<< this << ")" << std::endl; }
    Vector(const Vector& src) { std::cout << "Vector(this="<< this << ", src=" << &src << ")" << std::endl; }
    ~Vector() { std::cout << "~Vector(" << this << ")" << std::endl; }
    int mX;
    double mD;
};

void PrintVector(Vector vec)
{
    std::cout << "{x=" << vec.mX << ", d=" << vec.mD << "}" << std::endl;
}

int main(int argc, char** argv)
{
    Vector v;
    v.mX = 5;
    v.mD = 3.14;
    
    for(int i = 0; i < 5; i++)
    {
        Vector v2 = v;
    }
    
    PrintVector(v);
} 
