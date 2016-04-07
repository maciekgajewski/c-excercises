#include <iostream>
#include <stdexcept>

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
    throw std::runtime_error("I'm not printing this shit!");
    std::cout << "{x=" << vec.mX << ", d=" << vec.mD << "}" << std::endl;
}

void fun();

int main(int argc, char** argv)
{
    try
    {
        fun();
    }
    catch(const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}

void fun()
{
    std::cout << "main begin" << std::endl;
    Vector v;
    v.mX = 5;
    v.mD = 3.14;
    
    PrintVector(v);
    std::cout << "main end" << std::endl;
} 
