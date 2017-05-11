#include <iostream>
#include <string>

#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std::literals;

enum class PersonTypes { Persons, Employees, Servicemen };

struct Person

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
	
	std::string GetType() const { return "Person"; }
};

std::ostream& operator<<(std::ostream& s, const Person& p)
{
	return s << "{" << p.name << ", aged " << p.age << "}";
}

struct Record
{
	int id;
};

struct Employee : Record, Person
{
	std::string role;
	std::string GetType() const { return "Employee"; }
};

std::ostream& operator<<(std::ostream& s, const Employee& p)
{
	return s << "{ id=" << p.id << " " << p.name << ", aged " << p.age << ", role: " << p.role << "}";
}

void PrintRecord(const Record& r)
{
	std::cout << "Record id=" << r.id << std::endl;
}

int main(int /*argc*/, char** /*argv*/)
{
	Employee e;
	e.name = "John Doe";
	e.age = 66;
	e.role = "Janitor";
	e.id = 7777;
	e.type = PersonTypes::Employees;
	
	Person* p = &e;
	
	std::cout << "sizeof(Person) = " << sizeof(Person) << std::endl;
	std::cout << "sizeof(Employee) = " << sizeof(Employee) << std::endl;
	std::cout << "&e = " << &e << std::endl;
	std::cout << "p = " << p << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "*p = " << *p << std::endl;
	
	std::vector<Person*> ppl;
	
	Person josef { PersonTypes::Persons, "Josef", 28 };
	ppl.push_back(&e);
	ppl.push_back(&josef);
	
	PrintRecord(e);
	
	for(Person* p : ppl)
	{
		if (p->type == PersonTypes::Employees)
		{
			Employee* pe = static_cast<Employee*>(p);
			std::cout << pe->GetType() << " : " << *pe << std::endl;
		}
		else
			std::cout << p->GetType() << " : " << *p << std::endl;
	}
}
