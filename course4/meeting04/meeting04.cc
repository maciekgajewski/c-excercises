#include <iostream>

struct Class
{
	// Default 
	Class() { std::cout << this << " Default constructed" << std::endl; }
	// Copy constructor
	Class(const Class& source) { std::cout << this << " Copied from " << &source << std::endl; }
	// Move constructor
	Class(Class&& source) { std::cout << this << " Moved from " << &source << std::endl; }
	
	// User-define
	explicit Class(const char* v) { std::cout << this << " Initialized with v=" << v << std::endl; }
	explicit Class(int a, int b) { std::cout << this << " Initialized with a=" << a << ", b=b" << std::endl; }
	// copy assignment
	Class& operator=(const Class& source) {
		std::cout << this << " Copy-assigned from " << &source << std::endl;
		return *this;
	}
	// move assignment
	Class& operator=(Class&& source) {
		std::cout << this << " Move-assigned from " << &source << std::endl;
		return *this;
	}
	
	~Class() { std::cout << this << " Destroyed" << std::endl; }
};

int main(int argc, char** argv)
{
	Class* c = new Class();
	Class b;
	
	//delete c;
	
}

