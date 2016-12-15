#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <boost/any.hpp>

#include <random>
#include <iostream>
#include <string>
#include <tuple>

using namespace std::literals;

boost::optional<std::string> get_greeting()
{
	std::random_device device;
	std::uniform_int_distribution<int> dist(0, 1);

	if (dist(device))
	{
		return "Hello, world!"s;
	}
	else
	{
		return boost::none;
	}
}

// template<typename ... Types>
// class variant
// {
// private:
// 	int type;
// 	char buffer[maxofsizes(Types...)];
// 	//...
// };

struct visitor
{
	void operator()(int) { std::cout << "int" << std::endl; }
	void operator()(double) { std::cout << "double" << std::endl; }
	void operator()(const std::string&) { std::cout << "string" << std::endl; }
};

int main(int argc, char** argv)
{
	boost::variant<int, double, std::string> v = "erty";
	visitor vtor;
	boost::apply_visitor(vtor, v);
	
	boost::apply_visitor([&](auto x) { std::cout << "the value is=" << x <<std::endl; }, v);
	
}

