#include <iostream>
#include <stdexcept>


struct Vector
{
    Vector() { std::cout << "Vector(this="<< this << ")" << std::endl; }
    Vector(const Vector& src) { std::cout << "Vector(this="<< this << ", src=" << &src << ")" << std::endl; }
    ~Vector() { std::cout << "~Vector(" << this << ")" << std::endl; }
    
    Vector(int x, double d) : mX(x), mD(d)
    {
        std::cout << "init constructor" << std::endl;
    }
    
    int mX;
    double mD;
};

struct Supervector
{
    Supervector() : a(6, 5.5) { std::cout << "Supervector(this="<< this << ")" << std::endl; }
    ~Supervector() { std::cout << "~Supervector(this="<< this << ")" << std::endl; }
    Vector a;
    Vector b;
};

class VectorPrinter
{
public:
    VectorPrinter(Vector& v) : mVec(v) {}
    
    void Print()
    {
        std::cout << "{x=" << mVec.mX << ", d=" << mVec.mD << "}" << std::endl;
    }
private:
    Vector& mVec;
};


Vector global;

int main(int argc, char** argv)
{
    Vector x(4, 5.6);
    VectorPrinter printer(x);
    printer.Print();
    
} 
