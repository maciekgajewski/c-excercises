#pragma once

#include "person.h"

class Professional : public Person
{
public:
	
	const std::string& GetProfession() const { return mProffesion; }
	void SetProfession(std::string p) { mProffesion = std::move(p); }
private:
	
	std::string mProffesion;
};

inline void ToXml(std::ostream& o, const Professional& p)
{
	o << "<Professional><Name>" 
	<< p.GetName() << "</Name><Age>" 
	<< p.GetAge() << "</Age><Profession>"
	<< p.GetProfession()
	<< "</Profession></Professional>";
}

