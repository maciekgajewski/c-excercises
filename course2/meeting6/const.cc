#include "string.hh"


void print_json(const MyString& s)
{
    std::cout
        << "{"
        << "string=\"" << s << "\","
        << "length=" << s.length()
        << "}"
        << std::endl;
}

int main()
{
    test_string();
    
    MyString hello = "Hello, World";
    MyString suffix = ".com";
    print_json(hello + suffix);
}