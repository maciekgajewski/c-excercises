#include <iostream>
#include <cstring>
#include "matchingEngine.h"
#include <sstream>

int main()
{
    course::MatchingEngine mathingEngine;
    std::string input;
    while(std::getline(std::cin, input))
    {
        std::stringstream ss;
        ss.str(input);
        std::string command;
        ss >> command;
        if(command == "insert")
        {
              course::Order order;
              std::string side;
              ss >> side;
              order.side = side == "buy" ? course::Buy : course::Sell;
              ss >> order.instrument >> order.id >> order.price >> order.volume;
              if(ss.fail())
              {
                  std::cout << "input error" << std::endl;
                  continue;
              }

              mathingEngine.InsertOrder(order);
        }
        else if(command == "delete")
        {
            std::string instrument;
            unsigned long orderId;
            ss >> instrument >> orderId;
            if(ss.fail())
            {
                std::cout << "input error" << std::endl;
                continue;
            }

            mathingEngine.DeleteOrder(instrument, orderId);
        }
        else
        {
            std::cout << "input error" << std::endl;
        }
    }

}
