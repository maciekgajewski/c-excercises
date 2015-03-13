#pragma once

#include "person.h"

class Professional : public Person
{
public:
	
	Professional(std::string name, int age, std::string prof)
		: Person(name, age), mProffesion(prof)
	{}
	
	const std::string& GetProfession() const { return mProffesion; }
	void SetProfession(std::string p) { mProffesion = std::move(p); }

	void ToXml(std::ostream& o) const override
	{
		o << "<Professional><Name>" 
		<< GetName() << "</Name><Age>" 
		<< GetAge() << "</Age><Profession>"
		<< GetProfession()
		<< "</Profession></Professional>";
	}
	
private:
	
	std::string mProffesion;
};


