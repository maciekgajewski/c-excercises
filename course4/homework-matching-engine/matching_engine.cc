#include "order_book.hh"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>

std::string read_substring(std::istringstream& iss)
{
	std::string sub;
	iss >> sub;
	return sub;
}

void input_error()
{
	std::cout << "input error" << std::endl;
}

void parse_input_line(const std::string& input_line, course::OrderBook& order_book)
{
	std::istringstream iss(input_line);
	std::string command_string = read_substring(iss);
	if (command_string == "insert")
	{
		std::string buy_sell_string = read_substring(iss);
		course::Side buy_sell_side;
		if (buy_sell_string == "buy")
		{
			buy_sell_side = course::Side::buy;
		}
		else if (buy_sell_string == "sell")
		{
			buy_sell_side = course::Side::sell;
		}
		else
		{
			input_error();
			return;
		}
		std::string instrument = read_substring(iss);
		std::uint64_t order_id;
		iss >> order_id;
		int price;
		iss >> price;
		int volume;
		iss >> volume;
		order_book.insert_order(buy_sell_side, instrument, order_id, price, volume);
	}
	else if (command_string == "delete")
	{
		std::string instrument = read_substring(iss);
		std::uint64_t order_id;
		iss >> order_id;
		order_book.delete_order(instrument, order_id);
	}
	else
	{
		input_error();
	}
}

int main()
{
	course::OrderBook order_book;
	for (std::string line; std::getline(std::cin, line);)
		parse_input_line(line, order_book);
}