#include "string.hh"
#include <cmath>

void print_json(const MyString& s)
{
    std::cout
        << "{"
        << "string=\"" << s << "\""
        << ", length=" << s.length()
        << ", first_char=" << s[0]
        << "}"
        << std::endl;
}


class Vec
{
public:
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    void setX(double xx) { x = xx; lenKnown = false;}
    void setY(double yy) { y = yy; lenKnown = false;}
    
    double getLen() const
    {
        if (!lenKnown)
        {
            
            lenCache = std::sqrt(x*x + y*y);
            lenKnown = true;
        }
        return lenCache;
    }
    
private:
    
    mutable bool lenKnown = false;
    mutable double lenCache;
    
    double x;
    double y;
};

int main()
{
    test_string();
    
    MyString hello = "Hello, World";
    MyString suffix = ".com";
    print_json(hello);
    
    std::cout << "hello=" << hello << std::endl;
 
    Vec v;
    v.setX(3.0);
    v.setY(4.0);
    
    std::cout << "len=" << v.getLen() << std::endl;
    
}