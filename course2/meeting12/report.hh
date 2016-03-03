#pragma once
#include "record.hh"
#include <ostream>

#include <vector>
namespace ReportingSystem {

void PrintReport(std::ostream& s, const std::vector<const Record*>& records);


}
