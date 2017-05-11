#include <iostream>
#include <string>

#include <vector>
#include <memory>

using namespace std::literals;

struct IStreamable
{
	virtual void ToStream(std::ostream& s) const = 0;
};

struct Person : IStreamable
{
	virtual ~Person() = default;
	
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
	std::vector<std::unique_ptr<Person>> ppl;

	auto e = std::make_unique<Employee>();
	e->name = "John Doe";
	e->age = 66;
	e->role = "Janitorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr";
	
	auto josef = std::make_unique<Person>();
	josef->name = "Josef";
	josef->age = 28;
	
	auto m = std::make_unique<Serviceman>();
	m->name = "Solider";
	
	ppl.push_back(std::move(e));
	ppl.push_back(std::move(josef));
	ppl.push_back(std::move(m));
	
	for(const std::unique_ptr<Person>& p : ppl)
	{
		std::cout << p->GetType() << " : " << *p << std::endl;
	}
}
