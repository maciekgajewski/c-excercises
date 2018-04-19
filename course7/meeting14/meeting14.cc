#include <iostream>
#include <string>
#include <memory>

struct IStreamable
{
	virtual void ToStream(std::ostream& s) const = 0;
	virtual ~IStreamable() {}
};

struct Person : IStreamable
{
	// vptr
	std::string name;
	double height;

	virtual void ToStream(std::ostream& s) const {  s << "Person{name: " << name << ", height: " <<height << "m}"; }
};

struct Employee : Person
{
	std::string role;
	void ToStream(std::ostream& s) const override {  s << "Employee{name: " << name << ", height: " << height << "m, role: " << role << "}"; }
};

std::ostream& operator<<(std::ostream& s, const IStreamable& p)
{
	p.ToStream(s);
	return s;
}

std::unique_ptr<Person> MakePerson(const std::string& type, const std::string& name)
{
	if (type == "employee")
	{
		auto e = std::make_unique<Employee>();
		e->name = name;
		e->role = "Developerxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		return e;
	}
	else
	{
		auto p = std::make_unique<Person>();
		p->name = name;
		return p;
	}
}

int main(int argc, char** argv)
{
	std::unique_ptr<Person> p = MakePerson(argv[1], argv[2]);
	std::cout << "Created: " << *p << std::endl;

	Employee& e = dynamic_cast<Employee&>(*p);
}
