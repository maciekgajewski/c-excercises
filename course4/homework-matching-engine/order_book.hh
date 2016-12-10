#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <unordered_set>
#include <map>
#include <array>
#include <algorithm>
#include <cstdint>

namespace course {

void print_invalid_order_error();

enum struct Side
{
	buy,
	sell
};

struct Order
{
	std::uint64_t order_id;
	int price;
	int volume;
	Side side;
};

class InstrumentOrderBook
//maintains all orders for one instrument
{
public:
	InstrumentOrderBook(const std::string& instrument) : instrument(instrument) {}

	void insert(Order order)
	{
		if (id_order_book.count(order.order_id)) // order with same id already in the book
		{
			print_invalid_order_error();
			return;
		}
		//first match order against existing orders
		if (order.side == Side::buy)
			match_order(order, sell_price_order_ids);
		else
			match_order(order, buy_price_order_ids);
		if (order.volume > 0) //some volume left, add to the book
		{
			auto order_id = order.order_id;
			id_order_book[order_id] = order;
			if (order.side == Side::buy)
				add_to_book(order_id, order.price, buy_price_order_ids);
			else
				add_to_book(order_id, order.price, sell_price_order_ids);
		}
		if (order.side == Side::buy)
			check_and_print_pricefeed(order, buy_price_order_ids);
		else
			check_and_print_pricefeed(order, sell_price_order_ids);
	}

	void remove(std::uint64_t order_id)
	{
		Order& order_to_remove= id_order_book.at(order_id);
		if (order_to_remove.side == Side::buy)
		{
			delete_order_from_side_price_order_ids(order_to_remove, buy_price_order_ids);
			check_and_print_pricefeed(order_to_remove, buy_price_order_ids);
		}
		else
		{
			delete_order_from_side_price_order_ids(order_to_remove, sell_price_order_ids);
			check_and_print_pricefeed(order_to_remove, sell_price_order_ids);
		}
		id_order_book.erase(order_id);
	}

private:
	std::map<int, std::unordered_set<std::uint64_t>, std::greater<int>> buy_price_order_ids;
	std::map<int, std::unordered_set<std::uint64_t>, std::less<int>> sell_price_order_ids;
	std::unordered_map<std::uint64_t, Order> id_order_book;
	std::string instrument;

	template<typename SidePriceOrderIdType>
	void check_and_print_pricefeed(const Order& order, const SidePriceOrderIdType& side_price_order_ids)
	//check whether we need to print a new price feed and if yes, print price feed
	{
		if (side_price_order_ids.empty() ||
				((order.side == Side::buy) && (order.price >= side_price_order_ids.begin()->first)) ||
				((order.side == Side::sell) && (order.price <= side_price_order_ids.begin()->first)))
			print_pricefeed();
	}

	void print_pricefeed()
	{
		std::cout << "pricefeed " << instrument << " " ;
		print_price_info(buy_price_order_ids);
		std::cout << " ";
		print_price_info(sell_price_order_ids);
		std::cout << std::endl;		
	}

	template<typename SidePriceOrderIdType>
	void print_price_info(const SidePriceOrderIdType& side_price_order_ids)
	{
		if (side_price_order_ids.empty())
		{
			std::cout << "-";
		}
		else
		{
			int top_level_price = side_price_order_ids.begin() -> first;
			const std::unordered_set<uint64_t>& top_level_order_ids = side_price_order_ids.begin() -> second;
			int top_level_volume = 0;
			for (std::uint64_t order_id: top_level_order_ids)
				top_level_volume += id_order_book[order_id].volume;
			std::cout << top_level_volume << "@" << top_level_price;
		}
	}

	template<typename OtherSideOrderIdsType>
	void match_order(Order& order, OtherSideOrderIdsType& other_side_order_ids)
	{
		while (!other_side_order_ids.empty() && (order.side == Side::buy)? order.price >= other_side_order_ids.begin()->first :
		                                                                   order.price <= other_side_order_ids.begin()->first) //we can match against resting orders
		{
			int this_price = other_side_order_ids.begin()->first;
			std::unordered_set<std::uint64_t>& order_ids_this_price = other_side_order_ids.begin()->second;
			int matched_on_this_level = 0;
			while (!order_ids_this_price.empty()) //orders left to match on this price level
			{
				auto order_id_to_match_iterator = order_ids_this_price.begin();
				Order& order_to_match = id_order_book[*order_id_to_match_iterator];
				int match_volume = std::min(order_to_match.volume, order.volume);
				matched_on_this_level += match_volume;
				order.volume -= match_volume;
				order_to_match.volume -= match_volume;
				if (order_to_match.volume == 0)
				{
					order_ids_this_price.erase(order_id_to_match_iterator);
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
	}

	template<typename ThisSideOrderIdsType>
	void add_to_book(std::uint64_t order_id, int order_price, ThisSideOrderIdsType& this_side_price_order_ids)
	{
		if (this_side_price_order_ids.count(order_price)) //already orders on this price
			this_side_price_order_ids[order_price].insert(order_id);
		else
			this_side_price_order_ids.emplace(order_price, std::unordered_set<std::uint64_t>{}).first->second.insert(order_id);
	}

	template<typename SidePriceOrderIdType>
	void delete_order_from_side_price_order_ids(const Order& order_to_remove, SidePriceOrderIdType& side_price_order_ids)
	{
		std::unordered_set<uint64_t>& order_ids_this_price = side_price_order_ids[order_to_remove.price];
		order_ids_this_price.erase(std::find(std::begin(order_ids_this_price), std::end(order_ids_this_price), order_to_remove.order_id));
		if (order_ids_this_price.empty())
			side_price_order_ids.erase(order_to_remove.price);
	}
};

class OrderBook
{
public:
	OrderBook() {}

	void insert_order(Side side, const std::string& instrument, std::uint64_t order_id, int price, int volume) 
	{
		if ((price <= 0) || (volume <= 0))
			print_invalid_order_error();
		auto iob_emplace_res = order_book.emplace(instrument, instrument);
		InstrumentOrderBook& instrument_order_book = iob_emplace_res.first->second;
		instrument_order_book.insert(Order{order_id, price, volume, side});
	}

	void delete_order(const std::string& instrument, std::uint64_t order_id) 
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
	std::unordered_map<std::string, InstrumentOrderBook> order_book;
};
}