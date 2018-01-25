#include <iostream>
#include <stdexcept>
#include <string>

int fib_call_counter = 0;

int fib(int i)
{
	fib_call_counter++;
	std::cout << "fib, i=" << i << ", &i=" << &i << std::endl;
	std::cout << "fcc=" << fib_call_counter << ", &fcc=" << &fib_call_counter << std::endl;
	if (i < 2)
		return 1;
	else
		return fib(i-1) +
			fib(i-2);
}

int main(int argc, char** argv)
{
	const char* msg = "Not enough params";
	if (argc < 2)
		throw std::runtime_error(msg);

	std::string arg1 = argv[1];
	int i = std::stoi(arg1);

	std::cout << "fib(" << i << ") = " << fib(i) << std::endl;

	std::cout << "&argc=" << &argc << std::endl;
	std::cout << "&argv=" << &argv << std::endl;
	std::cout << "&arg1=" << &arg1 << std::endl;
	std::cout << "&i   =" << &i << std::endl;
	std::cout << "msg  =" << reinterpret_cast<const void*>(msg) << std::endl;

	std::cout << "&main = " << reinterpret_cast<const void*>(&main) << std::endl;
	std::cout << "&fib  = " << reinterpret_cast<const void*>(&fib) << std::endl;
}
