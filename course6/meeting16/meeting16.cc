#include <iostream>
#include <string>
#include <stdexcept>

#include <boost/optional.hpp>

int divide(int a, int b)
{
	if (b == 0)
		//throw std::invalid_argument("Division by zero");
		throw "Division by zero";
	return a/b;
}

int sum(int a, int b) { return a+b; }

struct Guard
{
	Guard() { std::cout << "Guard created" << std::endl; }
	~Guard() { std::cout << "Guard destroyed" << std::endl; }
};

int calc(int a, int b, int c)
{
	Guard g;
	return sum(divide(a, b), c);
}

int main(int argc, char** argv)
{
	if (argc < 4)
		throw std::runtime_error("At least 3 arguments required");

	try
	{
		int a, b, c;
		try
		{
			a = std::stoi(argv[1]);
			b = std::stoi(argv[2]);
			c = std::stoi(argv[3]);
		}
		catch(...)
		{
			std::cout << "Error reading arguments" << std::endl;
			throw;
		}
			
		int result = calc(a, b, c);;

		std::cout << a << " / " << b << " + " << c << " = " << result << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	catch(const char* error)
	{
		std::cout << "Tijs's style error: " << error << std::endl;
	}
	catch(...)
	{
		std::cout << "Some weird error" << std::endl;
	}
}



int init_network()
{
	int r;

	r = init_hardware();
	if (r!=0)
		return -1;
	
	r = init_ip();
	if (!r)
		goto ip_failed;

	r = init_tcp():
	if (!r)
		goto tcp_failed;

	return 0; 
		
	tcp_failed:
	deinit_ip();

	ip_failed:
	deinit_hardware();
	return -1;
}






 