#pragma once

#include <string>
#include <boost/property_tree/ptree.hpp>


namespace Karun
{

class Transcoder
{
public:
	Transcoder() = default;
	Transcoder(const std::string& fileName);
	
	void ReadXML(const std::string& fileName);
	void ReadJSON(const std::string& fileName);
	void WriteXML(const std::string& fileName);
	void WriteJSON(const std::string& fileName);
	
private:
	boost::property_tree::ptree mData;
};

}
