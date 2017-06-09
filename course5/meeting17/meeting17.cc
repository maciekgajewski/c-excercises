#include <boost/variant.hpp>

#include <iostream>
#include <map>
#include <string>
#include <cstdint>
#include <iomanip>

using param_t = boost::variant<std::string, double, std::int64_t, bool>;
using param_map = std::map<std::string, param_t>;

void to_json(std::ostream& os, const param_map& map);

int main(int /*argc*/, char** /*argv*/)
{
	param_map params;
	
	params["strategy"] = std::string("AEX Basket");
	params["reference-price"] = 100.2;
	params["enabled"] = true;
	params["algoid"] = std::int64_t(4455);
	//params["algoid"] = 4455ll;
	
	to_json(std::cout, params);
	std::cout << std::endl;
}

struct param_to_json
{
	std::ostream& m_stream;
	
	void operator()(const std::string& s) { m_stream << '"' << s << '"'; }
	
	template<typename T>
	void operator()(const T& v) { m_stream << std::boolalpha << v; }
};

void to_json(std::ostream& os, const param_map& map)
{
	param_to_json visitor{os};
	
	os << "{";
	for(const auto& pair : map)
	{
		os << '"' << pair.first << "\":";
		boost::apply_visitor(visitor, pair.second);
		os << ',';
	}
	os << "}";
}


