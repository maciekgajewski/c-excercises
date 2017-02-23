#include <iostream>
#include <string>
#include <cassert>


int main(int /*argc*/, char** /*argv*/)
{
	std::string a; // default constructor std::string::string()
	std::string b = "Hello, world!"; // std::string::string(const char*)
	std::string c = b; // copy-construction
	
	assert(c == b);// operator ==
	b[1] = 'a'; // operator[]
	assert(c != b);// operator !=
	
	c = a; // copy-assignment (deep copy)
	c = "Hey"; // converting-assignment
	
	a = std::move(b); // move assignment
	std::string d = std::move(a); // move construction
}

