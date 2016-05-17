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
	
	bool operator==(const String& other) const;
	bool operator!=(const String& other) const { return !(*this == other); }
	
	char operator[](std::size_t index) const { return mBuffer[index]; }
	char& operator[](std::size_t index) { return mBuffer[index]; }
	
	const char* c_str() const;
	
	String operator+(const String& other) const;
	String& operator+=(const String& other);
	
	String& operator=(const String& other);
	
private:

	std::unique_ptr<char[]> mBuffer;
};

}