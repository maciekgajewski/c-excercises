#include <iostream>

namespace maciek
{
    
class Vector
{
    int x = 0;
    int y = 0;
};

}


namespace maciek
{
    class Square { int a; };
}

namespace Optiver { namespace IML { namespace Eurex {

    class Square { double f; };
    
}}}

int main()
{
    using namespace maciek;
    //std::cout 
    Vector v;
    Square s;
}

