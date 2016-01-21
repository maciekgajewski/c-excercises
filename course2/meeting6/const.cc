#include "string.hh"


void print_json(MyString s)
{
    std::cout
        << "{"
        << "string=\"" << s << "\""
        << "}"
        << std::endl;
}

int main()
{
    test_string();
    
    MyString hello = "Hello, World";
    print_json(hello);
}