#include "person.h"
#include "professional.h"

#include <iostream>
#include <vector>
#include <list>

template<typename Container>
void ToXml(const Container& ppl)
{
	std::cout << "<People>" << std::endl;
	for(const IXmlWritable* p : ppl)
	{
		p->ToXml(std::cout);
	}
	std::cout << "</People>" << std::endl;
}

int main()
{
	Person maciek("Maciek", 34);
	Person magda("Magda", 19);
	Professional pavlo("Pavlo", 26, "C++ Developer");
	
	std::cout << "sizeof person=" << sizeof(Person) << std::endl;
	std::cout << "sizeof prof=" << sizeof(Professional) << std::endl;
	
	//maciek.ToXml(std::cout);
	//pavlo.ToXml(std::cout)ToXml;
	
	IXmlWritable whatever;
	
 	std::list<IXmlWritable*> people;
// 	
 	people.push_back(&maciek);
 	people.push_back(&magda);
 	people.push_back(&pavlo);
// 	
 	ToXml(people);
	
}