#pragma once

#include <ostream>

#include <vector>
namespace ReportingSystem {

class Record;

void PrintReport(std::ostream& s, const std::vector<const Record*>& records);


}
