#include <iostream>
#include <memory>
#include <cassert>

#include "my_class.hh"

int main(int /*argc*/, char** /*argv*/)
{
	std::unique_ptr<char[]> a;
	assert(a.get() == nullptr);
	
	std::unique_ptr<char[]> b = std::make_unique<char[]>(7);
	std::unique_ptr<char[]> c = std::make_unique<char[]>(4);
	
	c = std::move(b);
	
}

