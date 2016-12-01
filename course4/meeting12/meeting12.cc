#include <iostream>
#include <stdexcept>
#include <memory>
#include <cassert>

class Person
{
public:

	using NameType = std::string;

	virtual void print() const
	{
		std::cout << "Person: " << mName << ", age: " << mAge << std::endl;
		std::cout << "this=" << this << std::endl;
		std::cout << "&mName=" << &mName << std::endl;
		std::cout << "&mAge=" << &mAge << std::endl;
	}
	
	Person(const NameType& name, int age) : mName(name), mAge(age) {}
private:
	
	NameType mName;
	int mAge;
};

class Record
{
public:
	Record(int id) : mId(id) {}
	int GetId() const { return mId; }
private:
	int mId;
};

class Employee : public Person, public Record
{
public:
	Employee(const std::string& p, const NameType& n, int a, int id) : Person(n, a), Record(id), mPosition(p) {}
	
	void print() const override final
	{
		std::cout << "Employee: position: " << mPosition << " ";
		Person::print();
	}
	
	virtual void paySalary() { std::cout << "yay!" << std::endl; }
private:
	NameType mPosition;
};

void report(const Person& person)
{
	std::cout << "=== REPORT ==" << std::endl;
	person.print();
	
	const Employee* e = dynamic_cast<const Employee*>(&person);
	if (e) 
	{
		std::cout << "this is an Employee, BTW" << std::endl;
	}
	const Employee& er = dynamic_cast<const Employee&>(person);
	
	std::cout << "=============" << std::endl;
}

int main(int argc, char** argv)
{
	Person p("Maciek", 36);
	p.print();
	
	Employee e("QT guy", "Ilya", 28, 666);
	e.print();

	std::cout << "Ilya's ID=" << e.GetId() << std::endl;
	
	std::cout << "&e=" << &e << std::endl;
	std::cout << "&e as person=" << static_cast<Person*>(&e) << std::endl;
	std::cout << "&e as record=" << static_cast<Record*>(&e) << std::endl;
	Record* r = reinterpret_cast<Record*>(&e);
	std::cout << "r=" << r << std::endl;
	std::cout << "r->id=" << r->GetId() << std::endl;
	
	report(p);
	report(e);
}

