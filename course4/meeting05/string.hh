#pragma once

#include <memory>
#include <ostream>

namespace maciek {

class string
{
public:

	string() = default;
	string(const char* data);
	
	std::size_t length() const { return mLength; }
	
private:
	
	std::unique_ptr<char[]> mData;
	//int x = 6;
	std::size_t mLength = 0;
};

inline std::ostream& operator<<(std::ostream& os, const string& s)
{
	os << "String!";
	return os;
}

}
