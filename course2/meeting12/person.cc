#include "person.hh"

Person::Person(const std::string& firstName, const std::string& lastName)
	: mFirstName(firstName), mLastName(lastName)
{
}

void Person::Print(std::ostream& s) const
{
	s << "Person: " << mFirstName << " " << mLastName << std::endl;
}
