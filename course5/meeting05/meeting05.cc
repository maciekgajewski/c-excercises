#include <iostream>
#include <string>
#include <cassert>


int main(int /*argc*/, char** /*argv*/)
{
	std::string a; // default constructor std::string::string()
	std::string b = "Hello"; // std::string::string(const char*)	
	std::string c = b; // copy-construction
	
	c = "12345";
	
	b = c;
	
	a = b + c; // +, std::string created, a.operator=(std::string&&), ~std::string

	
	
}

