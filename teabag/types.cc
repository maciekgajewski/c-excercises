#include "types.hh"

#include <boost/property_tree/json_parser.hpp>

#include <sstream>

namespace Teabag {

QString toJson(const Result& r)
{
	std::ostringstream ss;
	boost::property_tree::json_parser::write_json(ss, r, false);
	return QString::fromStdString(ss.str());
}


}
