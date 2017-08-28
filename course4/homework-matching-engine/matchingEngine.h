#pragma once

#include "orderBookEntry.h"
#include "orderBook.h"

#include <cstring>
#include <unordered_map>

#include <iostream>
#include <deque>

namespace course {

class MatchingEngine
{
public:
    void InsertOrder(Order& order)
    {
        OrderBook& orderBook = instrumentToOrderBook[order.instrument];
        orderBook.PerformMatching(order);
    }

    void DeleteOrder(const std::string& instrument, unsigned long orderId)
    {
        OrderBook& orderBook = instrumentToOrderBook[instrument];
        orderBook.DeleteOrder(orderId);
    }

private:
   std::unordered_map<std::string, OrderBook> instrumentToOrderBook;
};
}
