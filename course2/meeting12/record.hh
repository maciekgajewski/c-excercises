#pragma once

#include <ostream>

namespace ReportingSystem {

class Record
{
public:

	virtual void Print(std::ostream& o) const = 0;
};

}

