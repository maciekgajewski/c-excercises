#include <iostream>
#include <string>
#include <memory>

struct Person {
	std::string firstName;
	std::string lastName;

	void print() {
		std::cout << "Person{first: " << firstName << ", last:" << lastName << "}" << std::endl;
	}
};

struct Record {
	int id;
};

struct Employee : public Person, public Record {
	std::string position;

	void print() {
		std::cout << "Employee{first: " << firstName << ", last:" << lastName 
		<< ", position: " << position << "}" << std::endl;
	}
};

void print_empl(Employee* e)
{
	e->print();
}

int main(int argc, char** argv)
{
	Employee p;
	p.firstName = "Dan"; p.lastName= "Collier"; p.position = "C++ Developer";
	std::cout << "sizeof p=" << sizeof(p) << std::endl;
	std::cout << "sizeof std:string=" << sizeof(std::string) << std::endl;
	std::cout << "addr of p=" << &p <<", addr of p.firstName=" << &p.firstName << std::endl;
	
	p.print();
	
	Person* pptr = &p;
	void* vptr = pptr;
	
	Record* rptr = &p;
	void* rec_vptr = &rptr;
	
	std::cout << "pptr=" << pptr << ", vptr=" << vptr << ", rptr=" << rptr 
		<< ", rec_vptr=" << rec_vptr << std::endl;
	
	print_empl(static_cast<Employee*>(rec_vptr));
	
	pptr->print();
	
	auto pp = std::make_unique<Person>();
	pp->lastName = "L"; pp->firstName = "F";
	pp->print();
}