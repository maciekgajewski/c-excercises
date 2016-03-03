#pragma once

#include <vector>
namespace ReportingSystem {

class Record;

void PrintReport(std::ostream& s, const std::vector<Record*>& records);


}
