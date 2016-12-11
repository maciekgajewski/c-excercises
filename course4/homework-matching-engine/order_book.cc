#include "order_book.hh"

namespace course {

void print_invalid_order_error()
{
	std::cout << "invalid order error" << std::endl;
}

std::ostream& print_side(std::ostream& s, const TopOfBook& top_of_book, Side side)
{
	if (top_of_book.volume(side) == 0)
		s << "-";
	else
		s << top_of_book.volume(side) << "@" << top_of_book.price(side);
	return s;
}

std::ostream& operator<<(std::ostream& s, const TopOfBook& top_of_book)
{
	print_side(s, top_of_book, Side::buy);
	s << " ";
	return print_side(s, top_of_book, Side::sell);
}
}