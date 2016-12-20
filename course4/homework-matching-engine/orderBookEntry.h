#pragma once
#include "models.h"
#include <cstring>
#include <unordered_map>
#include <map>
#include <iostream>
#include <deque>

namespace course{

class OrderBookEntry
{
  public:
    OrderBookEntry():
        bids(), asks(), totalBidVolume(0), totalAskVolume(0)
    {
    }

    void PushBidOrder(Order& order)
    {
        bids.push_back(order);
        totalBidVolume += order.volume;
    }

    void PushAskOrder(Order& order)
    {
        asks.push_back(order);
        totalAskVolume += order.volume;
    }

    int Buy(Order& order, std::unordered_map<unsigned long, Order> & activeOrders);

    int Sell(Order& order, std::unordered_map<unsigned long, Order> & activeOrders);

    unsigned int GetAskVolume() const
    {
        return totalAskVolume;
    }

    unsigned int GetBidVolume() const
    {
        return totalBidVolume;
    }

    void CancelBidOrder(unsigned long orderId);

    void CancelAskOrder(unsigned long orderId);

  private:
    std::deque<Order> bids;
    std::deque<Order> asks;
    unsigned int totalBidVolume;
    unsigned int totalAskVolume;
};

}
