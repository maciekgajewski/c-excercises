#include "report.hh"

#include "record.hh"

namespace ReportingSystem {

void PrintReport(std::ostream& s, const std::vector<const Record*>& records)
{
	s << "======= Report begin =======" << std::endl;
	for(const Record* r : records)
	{
		r->Print(s);
	}
	s << "=== Report end, " << records.size() << " records ===" << std::endl;
}

}
