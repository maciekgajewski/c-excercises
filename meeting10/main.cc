#include <iostream>
#include <stdexcept>
#include <string>

struct MyException
{
    std::string msg;
};

void somefun()
{
    throw MyException{"oh noes!"};
}

void wrap() noexcept
{
    try
    {
        somefun();
    }
    catch(MyException& e)
    {
        std::cerr << "wrapper cougth exception : " << e.msg << std::endl;
        e.msg = "wrapped: " + e.msg;
        throw;
    }
}

int main()
{
    std::cout << "Hello, world!" << std::endl;
    try
    {
        //somefun();
        wrap();
    }
    catch(MyException& e)
    {
        std::cerr << "Error: " << e.msg << std::endl;
    }
}
