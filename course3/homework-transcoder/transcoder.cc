#include "transcoder.h"

#include <string>
#include <exception>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>


Karun::Transcoder::Transcoder(const std::string& fileName)
{
	if (fileName.substr(fileName.size() - 4) == ".xml")
		Karun::Transcoder::ReadXML(fileName);
	else if (fileName.substr(fileName.size() - 5) == ".json")
		Karun::Transcoder::ReadJSON(fileName);
	else
		throw std::logic_error("Unknown file format - expected .xml or .json");
}

void Karun::Transcoder::ReadXML(const std::string& fileName)
{
	boost::property_tree::xml_parser::read_xml(fileName, mData);
}

void Karun::Transcoder::ReadJSON(const std::string& fileName)
{
	boost::property_tree::json_parser::read_json(fileName, mData);
}

void Karun::Transcoder::WriteXML(const std::string& fileName)
{
	boost::property_tree::xml_parser::write_xml(fileName, mData);
}

void Karun::Transcoder::WriteJSON(const std::string& fileName)
{
	boost::property_tree::json_parser::write_json(fileName, mData);
}
