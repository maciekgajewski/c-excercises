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
#include <tuple>

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
	
	auto t = std::make_tuple(1, 4.4, a);
	std::tuple<int, double ,double> y = t;
	
	auto t0 = std::get<0>(y);
	auto t1 = std::get<1>(y);
	
	
}

std::tuple<int, std::string> fun();

int a;
std::string s;

std::tie(a, s) = fun();

struct point { int x, int y;

bool operator==(const point& other) { return std::tie(x, y) == std::tie(other.x, other.y); }

