#include "orderBook.h"

namespace course{

void OrderBook::PerformMatching(Order & order)
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
            AddBidOrder(order, priceLevel);
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
                AddBidOrder(order, priceLevel);
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
                    AddBidOrder(order, priceLevel);
                    bestBid = order.price;
                }
            }
        }
    }
    else
    {
        if(priceLevel.GetAskVolume() != 0) //matching not possible, not wasting time on attempt
        {
            AddAskOrder(order, priceLevel);
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
                AddAskOrder(order, priceLevel);
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
                    AddAskOrder(order, priceLevel);
                    bestAsk = order.price;
                }
            }
        }
    }

    if(priceFeedRequired)
    {
        ProducePriceFeed(order.instrument);
    }
}

void OrderBook::AddBidOrder(Order &order, OrderBookEntry& priceLevel)
{
    priceLevel.PushBidOrder(order);
    activeOrders[order.id] = order;
}

void OrderBook::AddAskOrder(Order &order, OrderBookEntry& priceLevel)
{
    priceLevel.PushAskOrder(order);
    activeOrders[order.id] = order;
}

void OrderBook::DeleteOrder(unsigned long orderId)
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

void OrderBook::ProducePriceFeed(const std::string& instrument) const
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

}
