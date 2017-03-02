#include <iostream>
#include <string>
#include <cassert>


int main(int /*argc*/, char** /*argv*/)
{
	std::string a; // default constructor std::string::string()
	std::string b = "Hello"; // std::string::string(const char*)
	std::string c = b; // copy-construction
	
	((std::cout << b) << " world!") << std::endl;
	
}

