#include "json_sink.hh"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace Teabag {

using PTree = boost::property_tree::ptree;

JsonSink::JsonSink(std::ostream& s)
	: stream_(s)
{
}

void JsonSink::debuggerOutput(const std::string& out)
{
	PTree pt;
	pt.push_back({"type", PTree("debugger-output")});
	pt.push_back({"output", PTree(out)});

	boost::property_tree::json_parser::write_json(
		stream_, pt, false);
}

void JsonSink::targetOutput(const std::string& out)
{
	PTree pt;
	pt.push_back({"type", PTree("target-output")});
	pt.push_back({"output", PTree(out)});

	boost::property_tree::json_parser::write_json(
		stream_, pt, false);
}

} // namespace Teabag
