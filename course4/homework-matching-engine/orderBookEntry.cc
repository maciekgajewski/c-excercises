#include "orderBookEntry.h"

namespace course {

int OrderBookEntry::Buy(Order& order, std::unordered_map<unsigned long, Order> & activeOrders)
{
   int lotsBought = 0;
   while(order.volume > 0 && !asks.empty())
   {
       Order& topPriority = asks.front();
       if(order.volume > topPriority.volume)
       {
          lotsBought += topPriority.volume;
          totalAskVolume -= topPriority.volume;
          order.volume -= topPriority.volume;
          activeOrders.erase(topPriority.id);
          asks.pop_front();
       }
       else
       {
           lotsBought += order.volume;
           topPriority.volume -= order.volume;
           totalAskVolume -= order.volume;
           order.volume = 0;
       }
   }

   return lotsBought;
}

int OrderBookEntry::Sell(Order& order, std::unordered_map<unsigned long, Order> & activeOrders)
{
    int lotsSold = 0;
    while(order.volume > 0 && !bids.empty())
    {
        Order& topPriority = bids.front();
        if(order.volume > topPriority.volume)
        {
           lotsSold += topPriority.volume;
           totalBidVolume -= topPriority.volume;
           order.volume -= topPriority.volume;
           activeOrders.erase(topPriority.id);
           asks.pop_front();
        }
        else
        {
            lotsSold += order.volume;
            topPriority.volume -= order.volume;
            totalBidVolume -= order.volume;
            order.volume = 0;
        }
    }

    return lotsSold;
}

void OrderBookEntry::CancelBidOrder(unsigned long orderId)
{
    for(auto it = bids.begin(); it != bids.end(); ++it)
    {
        if(it->id == orderId)
        {
            totalBidVolume -= it->volume;
            bids.erase(it);
            return;
        }
    }
}

void OrderBookEntry::CancelAskOrder(unsigned long orderId)
{
    for(auto it = asks.begin(); it != asks.end(); ++it)
    {
        if(it->id == orderId)
        {
            totalAskVolume -= it->volume;
            asks.erase(it);
            return;
        }
    }
}
}
