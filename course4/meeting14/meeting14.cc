#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <boost/any.hpp>

#include <random>
#include <iostream>
#include <string>
#include <tuple>
#include <functional>
#include <sstream>

using namespace std::literals;

double add(double x, double y) { return x + y; };

int main(int argc, char** argv)
{
	std::function<double(double, double)> myFun = add;
	
	myFun = [f=myFun](double a, double b) {
		std::cout << "== BEGIN ==" << std::endl;
		double x = f(a,b);
		std::cout << "== END ==" << std::endl;
		return x;
	};
	
	if (myFun)
	{
		double x = myFun(5, 7.7);
		std::cout << "x=" << x << std::endl;
		std::ostringstream s;
		s << "the value is: " << x;
		
		std::cout << s.str() << std::endl;
	}
	else
	{
		std::cout << "not set" << std::endl;
	}
	
	auto b = std::bind(add, 4, 5);
	x = b();
	
}

