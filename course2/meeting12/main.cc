#include "person.hh"
#include "report.hh"

#include <boost/range/algorithm.hpp>

#include <iostream>

int main()
{
	Person participants[] = {
		{"Zach", "P"},
		{"Franchesca", "M"},
		{"Matthijs", "S"},
	};

	std::vector<const ReportingSystem::Record*> records;

	boost::transform(participants, std::back_inserter(records), 
		[&](const Person& p) { return &p; });

	ReportingSystem::PrintReport(std::cout, records);
	
}
