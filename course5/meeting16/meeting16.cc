#include <boost/filesystem.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <thread>
#include <atomic>
#include <random>
#include <functional>
#include <map>


using Oper = std::function<double(double, double)>;

double add(double a, double b) { return a+b; }

struct sub
{
	double operator()(double a, double b) const { return a-b; }
};

double do_something(const std::string& op, double a, double b)
{
	std::map<std::string, Oper> operations;
	
	operations["+"] = add;
	operations["-"] = sub{};
	operations["*"] = [](double a, double b) { return a*b; };
	operations["/"] = [](double a, double b) { return a/b; };
	
	auto it = operations.find(op);
	if (it == operations.end())
	{
		throw std::runtime_error("Unknown operation");
	}
	
	Oper& o = it->second;
	return o(a, b);
}

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		std::cout << "3 params required!" << std::endl;
		return 2;
	}
	
	std::string operation = argv[3];
	double a = std::stod(argv[1]);
	double b = std::stod(argv[2]);
	
	// some magic
	double result = do_something(operation, a , b);
	std::cout << result << std::endl;
	
	
}


