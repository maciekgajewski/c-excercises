#pragma once

#include "record.hh"


// hello!
class Person : public ReportingSystem::Record
{
public:

	Person(const std::string& firstName, const std::string& lastName);

	void Print(std::ostream& s) const override;

	void SetiFirstName(const std::string& fn) { mFirstName = fn; }
	void SetLastName(const std::string& ln) { mLastName = ln; }

private:

	std::string mFirstName;
	std::string mLastName;
};
