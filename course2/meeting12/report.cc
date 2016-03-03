#include "report.hh"

#include "record.hh"

namespace ReportingSystem {

void PrintReport(std::ostream& s, const std::vector<Record*>& records)
{
	s << "======= Report begin =======" << std::endl;
	for(Record* r : records)
	{
		r->Print(s);
	}
	s << "=== Report end, " << records.size() << " records ===" << std::endl;
}

}
