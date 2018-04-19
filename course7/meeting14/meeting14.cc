#include <iostream>
#include <string>

struct ID 
{
	std::int64_t id;
};

struct IStreamable
{
	virtual void ToStream(std::ostream& s) const = 0;
};

struct Person : IStreamable
{
	// vptr
	std::string name;
	double height;

	virtual void ToStream(std::ostream& s) const {  s << "Person{name: " << name << ", height: " <<height << "m}"; }
};

struct Employee : ID, Person
{
	std::string role;
	void ToStream(std::ostream& s) const override {  s << "Employee{name: " << name << ", height: " << height << "m}"; }
};

std::ostream& operator<<(std::ostream& s, const IStreamable& p)
{
	p.ToStream(s);
	return s;
}

void PrintId(const ID& id)
{
	std::cout << "id=" << id.id << ", &id=" << &id << std::endl;
}

int main(int argc, char** argv)
{
	Person maciek;
	maciek.name = "Maciek";
	maciek.height = 2.00;
	std::cout << maciek << std::endl;

	Employee fred;
	fred.role = "Developer";
	fred.name = "Fred";
	fred.height = 1.68;
	fred.id = 666;

	std::cout << "sizeof string: " << sizeof(std::string) << std::endl;
	std::cout << "sizeof Person: " << sizeof(Person) << std::endl;
	std::cout << "sizeof Employee: " << sizeof(Employee) << std::endl;

	Person& fredsEvilPersonality = reinterpret_cast<Person&>(fred); // Evil!!!
	Person& fredAsPerson = static_cast<Person&>(fred);
	ID& fredAsId = static_cast<ID&>(fred);

	std::cout << "&fred=" << &fred << std::endl;
	std::cout << "&fredAsPerson=" << &fredAsPerson << std::endl;
	std::cout << "&fredAsId=" << &fredAsId << std::endl;
	std::cout << "fredsEvilPersonality=" << &fredsEvilPersonality << std::endl;

	std::cout << fred << std::endl;
	PrintId(fred);
}
