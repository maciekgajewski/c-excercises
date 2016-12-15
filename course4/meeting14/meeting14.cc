#include <boost/optional.hpp>

#include <random>
#include <iostream>
#include <string>

using namespace std::literals;

boost::optional<std::string> get_greeting()
{
	std::random_device device;
	std::uniform_int_distribution<int> dist(0, 1);

	if (dist(device))
		return "Hello, world!"s;
	else
		return boost::none;
}


int main(int argc, char** argv)
{
	auto greeting = get_greeting();
	if (greeting)
		std::cout << *greeting << std::endl;
}

