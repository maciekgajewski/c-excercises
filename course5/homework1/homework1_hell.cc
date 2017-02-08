
// DISCLAIMER!!! THIS IS VERY WRONG APPROACH TO C++ HOMEWORKS (and to C++ in general)

#include <iostream>
#include <functional>
using namespace std;

const int MAX_NUM_ARGS = 445;

template <int I>
void print(void)
{
    print<I - 1>();
    std::cout << I << " " << std::endl;
}

template <>
void print<0>(void)
{
    std::cout << "0" << std::endl;
}

std::function<void(void)> printers[MAX_NUM_ARGS];

template<int I>
void definePrinters()
{
    printers[I] = [](){ print<I>(); };
    definePrinters<I - 1>();
}

template<>
void definePrinters<0>()
{
    printers[0] = &print<0>;
}

int main(int argc, char **argv)
{
    definePrinters<MAX_NUM_ARGS>();
    printers[argc - 1]();
    return 0;
}
