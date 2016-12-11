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

struct TopOfBook;

void print_invalid_order_error();
std::ostream& operator<<(std::ostream& s, const TopOfBook& top_of_book);

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

struct TopOfBook
//maintains the top of book price and volume. Side is empty is equivalent to volume(side) == 0 (price can be stale in this case)
{
	int bid_price;
	int bid_volume;
	int ask_price;
	int ask_volume;

	int& price(Side side)
	{
		return (side == Side::buy) ? bid_price : ask_price;
	}

	int& volume(Side side)
	{
		return (side == Side::buy) ? bid_volume : ask_volume;
	}

	int price(Side side) const
	{
		return (side == Side::buy) ? bid_price : ask_price;
	}

	int volume(Side side) const
	{
		return (side == Side::buy) ? bid_volume : ask_volume;
	}
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

		bool need_to_print_new_pricefeed;
		if (top_of_book.volume(order.side) == 0)
			need_to_print_new_pricefeed = true;
		else
			need_to_print_new_pricefeed = (order.side == Side::buy) ? ((order.price) >= top_of_book.price(Side::buy)) : ((order.price) <= top_of_book.price(Side::sell));

		//first match order against existing orders
		if (order.side == Side::buy)
			match_order(order, sell_price_order_ids);
		else
			match_order(order, buy_price_order_ids);

		if (order.volume > 0) //some volume left, add to the book
		{
			id_order_book[order.order_id] = order;
			if (order.side == Side::buy)
				add_to_book(order, buy_price_order_ids);
			else
				add_to_book(order, sell_price_order_ids);
			if (need_to_print_new_pricefeed) //order was added to top level, need to adjust top of book on order side
			{
				if ((top_of_book.volume(order.side) == 0) || (order.price != top_of_book.price(order.side))) //first order on this side or order improves top of book price
				{
					top_of_book.price(order.side) = order.price;
					top_of_book.volume(order.side) = order.volume;
				}
				else //order is on top of book price, i.e. order.price == top_of_book.price(order.side)
				{ 
					top_of_book.volume(order.side) += order.volume;
				}				
			}
		}
		if (need_to_print_new_pricefeed)
			print_pricefeed();
	}

	void remove(std::uint64_t order_id)
	{
		Order& order_to_remove= id_order_book.at(order_id);
		bool need_to_print_new_pricefeed = (order_to_remove.price == top_of_book.price(order_to_remove.side));
		if (order_to_remove.side == Side::buy)
			delete_order_from_side_price_order_ids(order_to_remove, buy_price_order_ids);
		else
			delete_order_from_side_price_order_ids(order_to_remove, sell_price_order_ids);
		if (need_to_print_new_pricefeed) //was a top level order, so need to adjust top of book
		{
			top_of_book.volume(order_to_remove.side) -= order_to_remove.volume;
			if (top_of_book.volume(order_to_remove.side) == 0) //top level price changes
			{
				if (order_to_remove.side == Side::buy)
					recalculate_top_of_book(buy_price_order_ids, order_to_remove.side);
				else
					recalculate_top_of_book(sell_price_order_ids, order_to_remove.side);
			}
		}
		id_order_book.erase(order_id);
		if (need_to_print_new_pricefeed)
			print_pricefeed();
	}

private:
	std::map<int, std::unordered_set<std::uint64_t>, std::greater<int>> buy_price_order_ids;
	std::map<int, std::unordered_set<std::uint64_t>, std::less<int>> sell_price_order_ids;
	std::unordered_map<std::uint64_t, Order> id_order_book;
	std::string instrument;
	TopOfBook top_of_book;

	void print_pricefeed()
	{
		std::cout << "pricefeed " << instrument << " " << top_of_book << std::endl;
	}

	template<typename SidePriceOrderIdType>
	void recalculate_top_of_book(const SidePriceOrderIdType& side_price_order_ids, Side side)
	{
		if (side_price_order_ids.empty())
		{
			top_of_book.volume(side) = 0;
		}
		else
		{
			top_of_book.price(side) = side_price_order_ids.begin() -> first;
			const std::unordered_set<uint64_t>& top_level_order_ids = side_price_order_ids.begin() -> second;
			int top_level_volume = 0;
			for (std::uint64_t order_id: top_level_order_ids)
				top_level_volume += id_order_book[order_id].volume;
			top_of_book.volume(side) = top_level_volume;
		}
	}

	template<typename SidePriceOrderIdType>
	void match_order(Order& order, SidePriceOrderIdType& other_side_order_ids)
	{
		Side passive_side = (order.side == Side::buy) ? Side::sell : Side::buy;
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
			if (this_price == top_of_book.price(passive_side)) // match happened at top level
				top_of_book.volume(passive_side) -= matched_on_this_level;
			std::cout << "tradefeed " << instrument << " " << matched_on_this_level << "@" << this_price << std::endl;
			if (order_ids_this_price.empty()) //level empty, delete from map
				other_side_order_ids.erase(this_price);
			if (order.volume == 0) //nothing more to match
				break;
		}
		if (top_of_book.volume(passive_side) == 0) //top of book got invalidated or was invalid already
		{
			if (passive_side == Side::buy)
				recalculate_top_of_book(buy_price_order_ids, passive_side);
			else
				recalculate_top_of_book(sell_price_order_ids, passive_side);
		}
	}

	template<typename SidePriceOrderIdType>
	void add_to_book(const Order& order, SidePriceOrderIdType& this_side_price_order_ids)
	{
		if (this_side_price_order_ids.count(order.price)) //already orders on this price
			this_side_price_order_ids[order.price].insert(order.order_id);
		else
			this_side_price_order_ids.emplace(order.price, std::unordered_set<std::uint64_t>{}).first->second.insert(order.order_id);
	}

	template<typename SidePriceOrderIdType>
	void delete_order_from_side_price_order_ids(const Order& order_to_remove, SidePriceOrderIdType& side_price_order_ids)
	{
		std::unordered_set<uint64_t>& order_ids_this_price = side_price_order_ids[order_to_remove.price];
		order_ids_this_price.erase(order_to_remove.order_id);
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