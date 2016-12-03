#include "order_book.hh"

#include <iostream>
#include <string>
#include <sstream>

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

template<typename PriceType, typename VolumeType>
void parse_input_line(const std::string& input_line, course::OrderBook<PriceType, VolumeType>& order_book)
{
	std::istringstream iss(input_line);
	std::string command_string = read_substring(iss);
	if (command_string == "insert")
	{
		std::string buy_sell_string = read_substring(iss);
		int buy_sell_side;
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
		std::string order_id = read_substring(iss);
		PriceType price;
		iss >> price;
		VolumeType volume;
		iss >> volume;
		order_book.insert_order(buy_sell_side, instrument, order_id, price, volume);
	}
	else if (command_string == "delete")
	{
		std::string instrument = read_substring(iss);
		std::string order_id = read_substring(iss);
		order_book.delete_order(instrument, order_id);
	}
	else
	{
		input_error();
	}
}

int main()
{
	course::OrderBook<int, int> order_book;
	for (std::string line; std::getline(std::cin, line);)
		parse_input_line(line, order_book);
}