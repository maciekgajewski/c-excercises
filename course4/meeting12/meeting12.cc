#include <iostream>
#include <stdexcept>
#include <memory>
#include <cassert>

class Person
{
public:

	using NameType = std::string;

	void print() const
	{
		std::cout << "Person: " << mName << ", age: " << mAge << std::endl;
		std::cout << "this=" << this << std::endl;
		std::cout << "&mName=" << &mName << std::endl;
		std::cout << "&mAge=" << &mAge << std::endl;
	}
	
	Person(const NameType& name, int age) : mName(name), mAge(age) {}

private:
	
	NameType mName;
	int mAge;
};

class Employee : public Person
{
private:
	
	NameType mPosition;
};

int main(int argc, char** argv)
{
	Person p("Maciek", 36);
	p.print();
	
	Employee e;
}

