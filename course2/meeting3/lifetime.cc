#include <iostream>

class Class
{
public:
	// Class::Class(Class* this) 
	Class() { std::cout << "Constructor, this=" << this << std::endl; }
	// Class::~Class(Class* this) 
	~Class() { std::cout << "Destructor, this=" << this <<std::endl; }
	// Class::Class(Class* this, const Class&)
	// Class& Class::operator=(Class* this, const Class& o)

	int x;
};

void SomeFunction(const Class& c)
{
	std::cout << "function, c=" << &c << std::endl;
}

void print(const char* s)
{
	std::cout << "s=" <<s << std::endl;
}

int main() // int(int, char**) 
{
	Class* ptr;
	{
		Class a; // Class::Class(&a);
		ptr = &a;
	}
	ptr->x = 6;
}

