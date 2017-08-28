#pragma once
#include <string>

namespace course{

enum Side
{
    Buy,
    Sell
};

struct Order
{
    Side side;
    unsigned int price;
    unsigned int volume;
    unsigned long id;
    std::string instrument;
};

}
