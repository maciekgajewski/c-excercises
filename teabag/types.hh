#pragma once

#include <boost/property_tree/ptree.hpp>

namespace Teabag {

using Result = boost::property_tree::ptree;

std::string toJson(const Result& r);

struct InputRecord
{
	int token;
	std::string inputClass;
	char type;
	Result result;
};

} // Teabag

