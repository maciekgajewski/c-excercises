#include <iostream>
#include <string>

#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std::literals;

struct Person

{
	std::string name;
	int age;
	
	bool operator < (const Person& p2) const
	{
		return this->age < p2.age;
	}
	bool operator > (const Person& p2) const
	{
		return this->age > p2.age;
	}
};

std::ostream& operator<<(std::ostream& s, const Person& p)
{
	return s << "{" << p.name << ", aged " << p.age << "}";
}

struct Employee : public Person
{
	std::string role;
};

std::ostream& operator<<(std::ostream& s, const Employee& p)
{
	return s << "{" << p.name << ", aged " << p.age << ", role: " << p.role << "}";
}

int main(int /*argc*/, char** /*argv*/)
{
	Employee e;
	e.name = "John Doe";
	e.age = 66;
	e.role = "Janitor";
	
	Person* p = &e;
	
	std::cout << "sizeof(Person) = " << sizeof(Person) << std::endl;
	std::cout << "sizeof(Employee) = " << sizeof(Employee) << std::endl;
	std::cout << "&e = " << &e << std::endl;
	std::cout << "p = " << p << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "*p = " << *p << std::endl;
	
	
}
