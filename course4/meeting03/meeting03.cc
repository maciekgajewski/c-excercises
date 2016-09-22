#include <iostream>
#include <string>

struct Class
{
	// Default 
	Class() { std::cout << this << " Default constructed" << std::endl; }
	// Copy constructor
	Class(const Class& source) { std::cout << this << " Copied from " << &source << std::endl; }
	// Move constructor
	Class(Class&& source) { std::cout << this << " Moved from " << &source << std::endl; }
	
	// User-define
	Class(const char* v) { std::cout << this << " Initialized with v=" << v << std::endl; }

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
	Class s1; // default construction
	Class s2("hey!"); // initilizing constructor
	Class s3(s2); // copy constructor
	Class* p = nullptr;
	{
		Class s4 = s2; // copy constructor
		s3 = s4; // copy assignment
		
		s1 = std::move(s2); // move assignment
		
		Class s5(std::move(s3)); // move construction
		p = &s5;
	}
	std::cout << "hello!!!, p=" << p << std::endl;
	
}

