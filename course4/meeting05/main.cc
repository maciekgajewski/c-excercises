#include "string.hh"
#include "person.hh"

#include <iostream>

#define HW "Hello, World!"
#ifdef __WIN32
int d = 5;
#endif

int main(int argc, char** argv)
{
	maciek::string s = HW;
	
	std::cout << s.length() << " " << s << std::endl;
}