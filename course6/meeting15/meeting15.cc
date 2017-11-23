#include <iostream>
#include <string>

class IPrintable
{
public:
	virtual void Print(std::ostream& o) const = 0;
};

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

class Employee : public Person
{
private:
	std::string role;
public:
	Employee(const std::string& n, int a, const std::string& r)
		: Person(n, a), role(r) {}

	void Print(std::ostream& o) const
	{ o << name << " the " << role << " (aged " << age << ")"; }
};

std::ostream& operator<<(std::ostream& o, const Person& p)
{
	p.Print(o);
	return o;
}

// std::ostream& operator<<(std::ostream& o, const Employee& p)
// {
// 	return o << p.name << " the " << p.role << " (aged " << p.age << ")";
// }

int main(int argc, char** argv)
{
	std::cout << "size of std::string: " << sizeof(std::string) << std::endl;
	std::cout << "size of Person: " << sizeof(Person) << std::endl;
	
	Employee maciek("Maciek", 37, "Teacher");

	std::cout << maciek << std::endl;
}
 