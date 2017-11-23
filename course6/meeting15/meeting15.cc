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

	virtual void Print(std::ostream& o) const
	{ o << name << " (aged " << age << ")"; }
};

struct DbEntry
{
	int name;
};

class Employee : public DbEntry, public Person
{
private:
	std::string role;
public:
	Employee(const std::string& n, int a, const std::string& r)
		: Person(n, a), role(r) { DbEntry::name = 7; }

	void Print(std::ostream& o) const
	{ o << Person::name << " the " << role << " (aged " << age << ")"; }
};


int main(int argc, char** argv)
{
	Employee maciek("Maciek", 37, "Teacher");
	Person misha("Misha", 31);

	std::cout << "&maciek=" << &maciek << std::endl;

	Person* p = &maciek;
	DbEntry* d = &maciek;
	std::cout << "p=" << p << std::endl;
	std::cout << "d=" << d << std::endl;

	// ?
	void* v = p;
	Employee* e = dynamic_cast<Employee*>(v);
	std::cout << "e=" << e << std::endl;
	e->Print(std::cout);

	std::cout << std::endl;

}
 