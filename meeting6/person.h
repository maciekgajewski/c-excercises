#pragma once

#include <string>
#include <iostream>

class IXmlWritable
{
public:
	virtual void ToXml(std::ostream& o) const = 0;
	virtual ~IXmlWritable() {}
};

class Person : public IXmlWritable
{
public:
	Person(std::string name, int age)
		: mName(std::move(name)), mAge(age)
	{
	}
	
	//Person(const Person& that)
	//{
	//}
	
	~Person()
	{
	}
	
	void SetName(const std::string& name) { mName = name; }
	void SetAge(int age) { mAge = age; }
	
	const std::string& GetName() const { return mName; }
	int GetAge() const { return mAge; }

	virtual void ToXml(std::ostream& o) const
	{
		o << "<Person><Name>" << GetName() 
		<< "</Name><Age>" << GetAge() << "</Age></Person>";
		std::cout << std::endl;
	}

private:
	
	std::string mName;
	int mAge = 7;
};


