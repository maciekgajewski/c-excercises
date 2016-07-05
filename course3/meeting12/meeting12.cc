#include <iostream>
#include <string>
#include <memory>

#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>

struct INamedClass {
	virtual std::string TypeName() const = 0;
};

struct Person : public INamedClass {
	std::string firstName;
	std::string lastName;

	virtual ~Person() {}
	std::string TypeName() const final { return "Person"; }
	
	virtual void ToStream(std::ostream& s) const {
		s << "first: " << firstName << ", last: " << lastName;
	}
};

struct Employee : public Person {
	std::string position;

	void ToStream(std::ostream& s) const {
		Person::ToStream(s);
		s << ", position: " << position;
	}
};

struct Car : public INamedClass {
	std::string make, model;
	std::string TypeName() const final { return "Type"; }
}

std::ostream& operator<<(std::ostream& s, const Person& p)
{
	s << "Type: " << p.TypeName() << ", ";
	p.ToStream(s);
	return s;
}

int main(int argc, char** argv)
{
	using namespace std::literals;
	
	Employee p;
	p.firstName = "Dan"; p.lastName= "Collier"; p.position = "C++ Developer";
	
	Person m;
	m.firstName = "Maciek"; m.lastName = "Gajewski";

	std::cout << p << std::endl;
	std::cout << m << std::endl;
	
	std::string ss = boost::lexical_cast<std::string>(p);
	
	
	
}