#pragma once
#include <boost/optional.hpp>
#include <cstring>
#include <unordered_map>
#include <map>
#include <iostream>
#include <deque>

namespace course {
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

    int Buy(Order& order, std::unordered_map<unsigned long, Order> & activeOrders)
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

    int Sell(Order& order, std::unordered_map<unsigned long, Order> & activeOrders)
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

    unsigned int GetAskVolume() const
    {
        return totalAskVolume;
    }

    unsigned int GetBidVolume() const
    {
        return totalBidVolume;
    }

    void CancelBidOrder(unsigned long orderId)
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

    void CancelAskOrder(unsigned long orderId)
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

  private:
    std::deque<Order> bids;
    std::deque<Order> asks;
    unsigned int totalBidVolume;
    unsigned int totalAskVolume;
};

struct OrderBook
{
    OrderBook()
        : bestBid(boost::none),
          bestAsk(boost::none),
          entries(),
          activeOrders()
    {
    }

    std::map<unsigned int, OrderBookEntry> entries;
    std::unordered_map<unsigned long, Order> activeOrders;
    boost::optional <unsigned int> bestBid;
    boost::optional <unsigned int> bestAsk;

    void ProducePriceFeed(const std::string& instrument) const
    {
        std::cout<<"pricefeed "<<instrument<<" ";
        if(bestBid)
        {
            auto& bestBidEntry = entries.at(*bestBid);
            std::cout << bestBidEntry.GetBidVolume() << "@" << *bestBid;
        }
        else
        {
            std::cout<<"-";
        }

        std::cout <<" ";
        if(bestAsk)
        {
            auto& bestAskEntry = entries.at(*bestAsk);
            std::cout << bestAskEntry.GetAskVolume() << "@" << *bestAsk;
        }
        else
        {
            std::cout<<"-";
        }

        std::cout<<std::endl;
    }

    void PerformMatching(Order & order)
    {
        auto duplicateOrder = activeOrders.find(order.id);
        if(duplicateOrder != activeOrders.end())
        {
            std::cout << "invalid order error" << std::endl;
            return;
        }

        OrderBookEntry& priceLevel = entries[order.price];
        bool priceFeedRequired = true;
        if(order.side == Side::Buy)
        {
            if(priceLevel.GetBidVolume() != 0) //matching not possible, not wasting time on attempt
            {
                priceLevel.PushBidOrder(order);
                activeOrders[order.id] = order;
                if(order.price != *bestBid)
                {
                    priceFeedRequired = false;
                }
            }
            else
            {
                if(!bestAsk ||
                        (bestAsk && bestAsk.get() > order.price)) // still no matching, inserting order
                {
                    priceLevel.PushBidOrder(order);
                    activeOrders[order.id] = order;
                    if(!bestBid || bestBid.get() < order.price)
                    {
                        bestBid = order.price;
                    }
                    else
                    {
                        priceFeedRequired = false;
                    }
                }
                else
                {
                    // matching
                    for(auto it = entries.find(*bestAsk); it != entries.end(); ++it)
                    {
                        if(!bestAsk)
                        {
                            if((it -> second).GetAskVolume() != 0)
                            {
                                bestAsk = it -> first;
                            }
                            else
                            {
                                continue;
                            }
                        }

                        if(it -> first > order.price || order.volume == 0)
                        {
                            break;
                        }

                        int lotsBought = (it->second).Buy(order, activeOrders);
                        if(lotsBought != 0)
                        {
                            std::cout<<"tradefeed " << order.instrument <<" "<<lotsBought<<"@"<<it->first<<std::endl;
                            if((it -> second).GetAskVolume() == 0)
                            {
                                bestAsk = boost::none;
                            }
                        }
                    }

                    if(order.volume != 0)
                    {
                        priceLevel.PushBidOrder(order);
                        activeOrders[order.id] = order;
                        if(!bestBid || bestBid.get() < order.price)
                        {
                            bestBid = order.price;
                        }
                    }
                }
            }
        }
        else
        {
            if(priceLevel.GetAskVolume() != 0) //matching not possible, not wasting time on attempt
            {
                priceLevel.PushAskOrder(order);
                activeOrders[order.id] = order;
                if(order.price != *bestAsk)
                {
                    priceFeedRequired = false;
                }
            }
            else
            {
                if(!bestBid ||
                        (bestBid && bestBid.get() < order.price)) // still no matching, inserting order
                {
                    priceLevel.PushAskOrder(order);
                    activeOrders[order.id] = order;
                    if(!bestAsk || bestAsk.get() > order.price)
                    {
                        bestAsk = order.price;
                    }
                    else
                    {
                        priceFeedRequired = false;
                    }
                }
                else
                {
                    // matching
                    for(auto it = entries.find(*bestBid); ; --it)
                    {
                        if(!bestBid)
                        {
                            if((it -> second).GetBidVolume() != 0)
                            {
                                bestBid = it -> first;
                            }
                            else
                            {
                                continue;
                            }
                        }

                        if(it -> first < order.price || order.volume == 0)
                        {
                            break;
                        }

                        int lotsSold = (it->second).Sell(order, activeOrders);
                        if(lotsSold != 0)
                        {
                            std::cout<<"tradefeed " << order.instrument <<" "<<lotsSold<<"@"<<it->first<<std::endl;
                            if((it -> second).GetBidVolume() == 0)
                            {
                                bestBid = boost::none;
                            }
                        }

                        if(it == entries.begin())
                        {
                            break;
                        }
                    }

                    if(order.volume != 0)
                    {
                        priceLevel.PushAskOrder(order);
                        activeOrders[order.id] = order;
                        if(!bestAsk || bestAsk.get() > order.price)
                        {
                            bestAsk = order.price;
                        }
                    }
                }
            }
        }

        if(priceFeedRequired)
        {
            ProducePriceFeed(order.instrument);
        }
    }

    void DeleteOrder(unsigned long orderId)
    {
        auto targetOrder = activeOrders.find(orderId);
        if(targetOrder == activeOrders.end())
        {
             std::cout << "invalid order error" << std::endl;
             return;
        }

        Order& order = targetOrder -> second;

        auto it = entries.find(order.price);
        OrderBookEntry& entry = it->second;
        if(order.side == Side::Buy)
        {
            entry.CancelBidOrder(order.id);
            if(order.price == *bestBid)
            {
                if(entry.GetBidVolume() == 0)
                {
                    bestBid = boost::none;
                    if(it != entries.begin())
                    {
                        do
                        {
                            --it;
                            if((it->second).GetBidVolume() != 0)
                            {
                                bestBid = it->first;
                                break;
                            }
                        }
                        while(it != entries.begin());
                    }
                }

                ProducePriceFeed(order.instrument);
            }
        }
        else
        {
            entry.CancelAskOrder(order.id);
            if(order.price == *bestAsk)
            {
                if(entry.GetAskVolume() == 0)
                {
                    ++it;
                    for(; it != entries.end(); ++it)
                    {
                        if((it->second).GetAskVolume() > 0)
                        {
                            bestAsk = it -> first;
                            break;
                        }
                    }
                }

                ProducePriceFeed(order.instrument);
            }
        }

        activeOrders.erase(targetOrder);
    }
};

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
