#include <iostream>
#include <string>

#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std::literals;

enum class PersonTypes { Persons, Employees, Servicemen };

struct IStreamable
{
	virtual void ToStream(std::ostream& s) const = 0;
};

struct Person : IStreamable
{
	PersonTypes type;
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
	
	virtual std::string GetType() const { return "Person"; }
	virtual void ToStream(std::ostream& s) const override { s << "{" << name << ", aged " << age << "}"; }
};


struct Employee : Person
{
	std::string role;
	std::string GetType() const override { return "Employee"; }
	virtual void ToStream(std::ostream& s) const override { s << "{" << name << ", aged " << age << ", role: " << role << "}"; }
};

struct Serviceman : Person
{
	// nope
	std::string GetType() const override { return "Serviceman"; }
	virtual void ToStream(std::ostream& s) const override { s << "{" << name << ", aged " << age << ", rank: " << rank << "}"; }
	
	std::string rank = "Private";
};

std::ostream& operator<<(std::ostream& s, const IStreamable& p)
{
	p.ToStream(s);
	return s;
}

int main(int /*argc*/, char** /*argv*/)
{
	Employee e;
	e.name = "John Doe";
	e.age = 66;
	e.role = "Janitor";
	e.type = PersonTypes::Employees;
	
	Person* p = &e;
	
	std::cout << "sizeof(Person) = " << sizeof(Person) << std::endl;
	std::cout << "sizeof(Employee) = " << sizeof(Employee) << std::endl;
	std::cout << "&e = " << &e << std::endl;
	std::cout << "p = " << p << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "*p = " << *p << std::endl;
	
	std::vector<Person*> ppl;
	
	Person josef;
	josef.type = PersonTypes::Persons;
	josef.name = "Josef";
	josef.age = 28;
	ppl.push_back(&e);
	ppl.push_back(&josef);
	
	Serviceman m;
	m.name = "Solider";
	
	ppl.push_back(&m);
	
	for(Person* p : ppl)
	{
		std::cout << p->GetType() << " : " << *p << std::endl;
	}
}
