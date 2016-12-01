#include <iostream>
#include <stdexcept>
#include <memory>
#include <cassert>

class Person
{
public:

	using NameType = std::string;

	virtual void print() const
	{
		std::cout << "Person: " << mName << ", age: " << mAge << std::endl;
		std::cout << "this=" << this << std::endl;
		std::cout << "&mName=" << &mName << std::endl;
		std::cout << "&mAge=" << &mAge << std::endl;
	}
	
	Person(const NameType& name, int age) : mName(name), mAge(age) {}

	virtual bool yes() = 0;
	
private:
	
	NameType mName;
	int mAge;
};



class Employee : public Person
{
public:
	
	Employee(const std::string& p, const NameType& n, int a) : Person(n, a), mPosition(p) {}
	
	void print() const override final
	{
		std::cout << "Employee: position: " << mPosition << " ";
		Person::print();
	}
	
	virtual void paySalary() { std::cout << "yay!" << std::endl; }
	
private:
	
	NameType mPosition;
};

void report(const Person& person)
{
	std::cout << "=== REPORT ==" << std::endl;
	person.print();
	std::cout << "=============" << std::endl;
}

int main(int argc, char** argv)
{
	Person p("Maciek", 36);
	p.print();
	
	Employee e("QT guy", "Ilya", 28);
	e.print();

	report(p);
	report(e);
}

