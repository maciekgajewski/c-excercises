#pragma once

#include <memory>

class MyString
{
public:

	MyString();
	MyString(const char*);
	MyString(const MyString&);
	
	std::size_t size() const;
	bool empty() const;
	
	bool operator==(const MyString& other);
	bool operator!=(const MyString& other);
	char& operator[](const unsigned i) const;
	
private:
	std::size_t mSize;
	std::unique_ptr<char[]> mBuffer;
};
