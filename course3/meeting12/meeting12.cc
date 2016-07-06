#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/any.hpp>


using OperFun = std::function<double(double, double)>;

double mul(double x, double y) { return x * y; }

double add(double a, double b, double c)
{
	return a + 2*b + c;
}

int main(int argc, char** argv)
{
	using namespace std::placeholders;
	
	std::map<std::string, OperFun> operations = {
		{ "+", [](double a, double b){ return add(a, 0 , b);} },
		{ "*", mul }
	};

	if (argc < 4)
		throw std::runtime_error("at least 3 params expected");
	double a = std::stod(argv[1]);
	std::string oper = argv[2];
	double b = std::stod(argv[3]);
	
	std::cout << a << " " << oper << " " << b << " = " << operations[oper](a, b) << std::endl;
	
	
	boost::any x = 5;
	std::cout << boost::any_cast<int>(x) << std::endl;
	
}