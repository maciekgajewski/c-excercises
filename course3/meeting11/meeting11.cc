#include <iostream>
#include <string>
#include <memory>

#include <boost/optional.hpp>

struct Person {
	std::string firstName;
	std::string lastName;

	virtual void print() {
		std::cout << "Person{first: " << firstName << ", last:" << lastName << "}" << std::endl;
	}
};

struct Employee : public Person {
	std::string position;

	void print() {
		std::cout << "Employee{first: " << firstName << ", last:" << lastName 
		<< ", position: " << position << "}" << std::endl;
	}
};

std::unique_ptr<Person> make_person(
	const std::string& f, const std::string& l, const boost::optional<std::string> pos = boost::none)
{
	std::unique_ptr<Person> p;
	if (!pos) {
		p = std::make_unique<Person>();
	}
	else {
		auto e = std::make_unique<Employee>();
		e->position = *pos;
		p = std::move(e);
	}
	p->firstName = f; p->lastName = l;
	return p;
}

int main(int argc, char** argv)
{
	using namespace std::literals;
	
	Employee p;
	p.firstName = "Dan"; p.lastName= "Collier"; p.position = "C++ Developer";
	std::cout << "sizeof p=" << sizeof(p) << std::endl;
	std::cout << "sizeof std:string=" << sizeof(std::string) << std::endl;
	std::cout << "addr of p=" << &p <<", addr of p.firstName=" << &p.firstName << std::endl;
	
	p.print();
	
	Person* pptr = &p;
	pptr->print();
	
	auto pp = make_person("Firstun", "Lasterson", "Position"s);
	pp->print();
	auto pp2 = make_person("Fred", "Flintstone");
	pp2->print();
}