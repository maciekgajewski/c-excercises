#include <iostream>
#include <stdexcept>
#include <string>

struct ComplexData
{
    int i;
    double d;
    std::string s;
    
    ComplexData() {}
    ComplexData(const ComplexData& o) : i(o.i), d(o.d), s(o.s) { std::cout << "copy" << std::endl; }
    ComplexData(ComplexData&& o) : i(o.i), d(o.d), s(std::move(o.s)) { std::cout << "move" << std::endl; }
    
    ComplexData& operator=(const ComplexData& o) {
        std::cout << "assignment" << std::endl; 
        
        i = o.i;
        d = o.d;
        s = o.s;
        return *this; }
};

ComplexData parse_args(int argc, char ** argv)
{
    if (argc > 5)
    {
        return ComplexData();
    }
    else
    {
        ComplexData result;
        result.i = argc;
        result.s = "parsed";
    
        return result;
    }
}

void print(const ComplexData& d) { std::cout<< "i=" << d.i << ", s=" << d.s << std::endl;  }

int main(int argc, char ** argv)
{
    ComplexData cd = parse_args(argc, argv);
    ComplexData a = cd;
    ComplexData b = std::move(cd);
    
    ComplexData* ptr = &a;
    ComplexData& ref = a;

    ref = b;
    *ptr = b;
    a = b;
    
    print(*ptr);
    print(ref);
    print(a);
}
