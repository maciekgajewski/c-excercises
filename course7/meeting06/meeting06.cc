#include <iostream>

struct Fred
{
	Fred() { std::cout << "Fred created, this=" << this << std::endl; }
	~Fred() { std::cout << "Fred destroyed, this=" << this << std::endl; }
};


int main(int argc, char** argv)
{
	Fred f;
	std::cout << "hello, world!" << std::endl;
}