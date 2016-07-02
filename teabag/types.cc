#include "types.hh"

#include <boost/property_tree/json_parser.hpp>

#include <sstream>

namespace Teabag {

std::string toJson(const Result& r)
{
	std::ostringstream ss;
	boost::property_tree::json_parser::write_json(ss, r, false);
	return ss.str();
}


}
