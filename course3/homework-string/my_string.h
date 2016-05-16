#pragma once

#include <memory>

namespace Maciek {

class String
{
public:

	String();
	String(const char*);
	String(const String&);
	
	std::size_t size() const;
	bool empty() const;
	
	bool operator==(const String& other);
	bool operator!=(const String& other);
	char& String::operator[](const int i) const;
	
private:
	std::size_t mSize;
	std::unique_ptr<char[]> mBuffer;
};

}