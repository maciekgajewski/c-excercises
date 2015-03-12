#pragma once

#include <string>
#include <iostream>

class Person
{
public:
	
	void SetName(std::string name) { mName = std::move(name); }
	void SetAge(int age) { mAge = age; }
	
	const std::string GetName() const { return mName; }
	int GetAge() const { return mAge; }
private:
	
	std::string mName;
	int mAge;
};

inline void ToXml(std::ostream& o, const Person& p)
{
	o << "<Person><Name>" << p.GetName() << "</Name><Age>" << p.GetAge() << "</Age></Person>";
}

