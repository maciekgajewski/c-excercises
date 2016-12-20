#pragma once

#include "orderBookEntry.h"
#include <boost/optional.hpp>
#include <map>

namespace course{

class OrderBook
{
public:
    OrderBook()
        : bestBid(boost::none),
          bestAsk(boost::none),
          entries(),
          activeOrders()
    {
    }

    void PerformMatching(Order& order);

    void DeleteOrder(unsigned long orderId);

private:
    void ProducePriceFeed(const std::string& instrument) const;

    inline void AddBidOrder(Order& order, OrderBookEntry& priceLevel);
    inline void AddAskOrder(Order& order, OrderBookEntry& priceLevel);

    std::map<unsigned int, OrderBookEntry> entries;
    std::unordered_map<unsigned long, Order> activeOrders;
    boost::optional <unsigned int> bestBid;
    boost::optional <unsigned int> bestAsk;
};

}
