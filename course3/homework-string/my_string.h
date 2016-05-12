#pragma once

#include <memory>

namespace Maciek {

class String
{
public:

	String() = default;
	String(const char*);
	String(const String&);
	
	std::size_t size() const;
	
	bool empty() const;
	
	bool operator==(const String& other);
	
private:

	std::unique_ptr<char[]> mBuffer;
};

}