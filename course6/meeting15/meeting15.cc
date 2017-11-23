#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class Person 
{
protected:
	std::string name;
	int age;

public:
	Person(const std::string& n, int a) : name(n), age(a) {}

	void Print(std::ostream& o) const
	{ o << name << " (aged " << age << ")"; }
};

struct DbEntry
{
	int id;
};

class Employee : public DbEntry, public Person
{
private:
	std::string role;
public:
	Employee(const std::string& n, int a, const std::string& r)
		: Person(n, a), role(r) { id = 7; }

	void Print(std::ostream& o) const
	{ o << name << " the " << role << " (aged " << age << ")"; }
};


int main(int argc, char** argv)
{
	Employee maciek("Maciek", 37, "Teacher");

	std::cout << "&maciek=" << &maciek << std::endl;

	Person* p = &maciek;
	DbEntry* d = &maciek;
	std::cout << "p=" << p << std::endl;
	std::cout << "d=" << d << std::endl;

	// ?
	Employee* e = static_cast<Employee*>(p);
	std::cout << "e=" << e << std::endl;
	e->Print(std::cout);

}
 