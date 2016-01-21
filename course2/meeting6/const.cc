#include "string.hh"


void print_json(MyString s)
{
    std::cout
        << "{string=\"" << s << "\", length="
        << s.length() << "}" << std::endl;
}

int main()
{
    test_string();
    
    MyString hello = "Hello, World";
    print_json(hello);
}