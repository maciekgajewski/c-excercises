#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <list>
#include <map>
#include <array>
#include <algorithm>

namespace course {

void print_invalid_order_error();

struct Side
{
	static const int buy = 0;
	static const int sell = 1;
};

template<typename PriceType, typename VolumeType>
struct Order
{
	std::string order_id;
	PriceType price;
	VolumeType volume;
	int side;
};

template<typename PriceType>
class PriceCompareFunctor
{
public:
	PriceCompareFunctor() : side(Side::sell) {}
	PriceCompareFunctor(int side) : side(side) {}
	
	bool operator() (PriceType lhs, PriceType rhs) const
	{
		if (side==Side::buy)
			return lhs > rhs;
		else
			return lhs < rhs;
	}

private:
	int side;
};

template<typename PriceType, typename VolumeType>
class InstrumentOrderBook
//maintains all orders for one instrument
{
public:
	InstrumentOrderBook(const std::string& instrument) : instrument(instrument) 
	{
		side_price_order_ids[Side::buy] = std::map<PriceType, std::list<std::string>, PriceCompareFunctor<PriceType>>(PriceCompareFunctor<PriceType>(Side::buy));
		side_price_order_ids[Side::sell] = std::map<PriceType, std::list<std::string>, PriceCompareFunctor<PriceType>>(PriceCompareFunctor<PriceType>(Side::sell));
	}
	
	void insert(Order<PriceType, VolumeType> order)
	{
		if (id_order_book.count(order.order_id)) // order with same id already in the book
		{
			print_invalid_order_error();
			return;
		}
		//first match order against existing orders
		int other_side = (order.side == Side::buy) ? Side::sell : Side::buy;
		std::map<PriceType, std::list<std::string>, PriceCompareFunctor<PriceType>>& other_side_order_ids = side_price_order_ids[other_side];
		while (!other_side_order_ids.empty() && (order.side == Side::buy)? order.price >= other_side_order_ids.begin()->first :
		                                                                   order.price <= other_side_order_ids.begin()->first) //we can match against resting orders
		{
			PriceType this_price = other_side_order_ids.begin()->first;
			std::list<std::string>& order_ids_this_price = other_side_order_ids.begin()->second;
			VolumeType matched_on_this_level = 0;
			while (!order_ids_this_price.empty()) //orders left to match on this price level
			{
				Order<PriceType, VolumeType>& order_to_match = id_order_book[order_ids_this_price.front()];
				VolumeType match_volume = std::min(order_to_match.volume, order.volume);
				matched_on_this_level += match_volume;
				order.volume -= match_volume;
				order_to_match.volume -= match_volume;
				if (order_to_match.volume == 0)
				{
					order_ids_this_price.pop_front();
					id_order_book.erase(order_to_match.order_id);
				}
				if (order.volume == 0)
					break;
			}
			std::cout << "tradefeed " << instrument << " " << matched_on_this_level << "@" << this_price << std::endl;
			if (order_ids_this_price.empty()) //level empty, delete from map
				other_side_order_ids.erase(this_price);
			if (order.volume == 0) //nothing more to match
				break;
		}
		if (order.volume > 0) //some volume left, add to the book
		{
			id_order_book[order.order_id] = order;
			side_price_order_ids[order.side].emplace(order.price, std::list<std::string>{}).first->second.push_back(order.order_id);
		}
		check_and_print_pricefeed(order);
	}

	void remove(const std::string& order_id)
	{
		Order<PriceType, VolumeType>& order_to_remove= id_order_book.at(order_id);
		std::list<std::string>& order_ids_this_price = side_price_order_ids[order_to_remove.side][order_to_remove.price];
		order_ids_this_price.erase(std::find(std::begin(order_ids_this_price), std::end(order_ids_this_price), order_id));
		if (order_ids_this_price.empty())
			side_price_order_ids[order_to_remove.side].erase(order_to_remove.price);
		check_and_print_pricefeed(order_to_remove);
		id_order_book.erase(order_id);
	}

private:
	std::array<std::map<PriceType, std::list<std::string>, PriceCompareFunctor<PriceType>>, 2> side_price_order_ids;
	std::unordered_map<std::string, Order<PriceType, VolumeType>> id_order_book;
	std::string instrument;

	void check_and_print_pricefeed(const Order<PriceType, VolumeType>& order)
	//check whether we need to print a new price feed and if yes, print price feed
	{
		if (side_price_order_ids[order.side].empty() ||
			((order.side == Side::buy) && (order.price >= side_price_order_ids[order.side].begin()->first)) ||
		    ((order.side == Side::sell) && (order.price <= side_price_order_ids[order.side].begin()->first)))
		{
			std::cout << "pricefeed " << instrument << " " ;
			print_price_info(Side::buy);
			std::cout << " ";
			print_price_info(Side::sell);
			std::cout << std::endl;
		}		
	}
	
	void print_price_info(int side)
	{
		if (side_price_order_ids[side].empty())
		{
			std::cout << "-";
		}
		else
		{
			PriceType top_level_price = side_price_order_ids[side].begin() -> first;
			std::list<std::string>& top_level_order_ids = side_price_order_ids[side].begin() -> second;
			VolumeType top_level_volume = 0;
			for (const std::string& order_id: top_level_order_ids)
				top_level_volume += id_order_book[order_id].volume;
			std::cout << top_level_volume << "@" << top_level_price;
		}
	}
};

template<typename PriceType, typename VolumeType>
class OrderBook
{
public:
	OrderBook() {}

	void insert_order(int side, const std::string& instrument, const std::string& order_id, const PriceType& price, const VolumeType& volume) 
	{
		auto iob_emplace_res = order_book.emplace(instrument, instrument);
		InstrumentOrderBook<PriceType, VolumeType>& instrument_order_book = iob_emplace_res.first->second;
		instrument_order_book.insert(Order<PriceType, VolumeType>{order_id, price, volume, side});
	}

	void delete_order(const std::string& instrument, const std::string& order_id) 
	{
		try
		{
			order_book.at(instrument).remove(order_id);
		}
		catch (const std::out_of_range& oor)
		{
			print_invalid_order_error();
		}
	}

private:
	std::unordered_map<std::string, InstrumentOrderBook<PriceType, VolumeType>> order_book;
};
}