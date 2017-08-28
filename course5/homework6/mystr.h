#pragma once 

#include <string>
#include <cstdio>
#include <iostream>
#include <memory>

// ARS -- week 06. 20170307

namespace mystring
{

class MyString
{
private:
	std::unique_ptr<char[]> mStr;
	void Reset_mStr(int new_size, const char* str);

public:
	MyString(); // default constructor
	MyString(const char* str); // User defined constructor

	MyString(const MyString& str);  // copy constructor
	MyString& operator = (const MyString& str);  // copy assignment
	MyString& operator = (const char* str); // assignment using char*

	MyString(const MyString&& str);  // move constructor
	MyString& operator = (const MyString&& str);  // move assignment
	
	char& operator[] (const size_t index); 
	const char& operator[] (const size_t index) const; 

	MyString  operator+ (const MyString& str); // concatenation
	MyString&  operator+= (const MyString& str); // concatenation assignment

	unsigned int length() const;
	const char* c_str() const; 
};

inline std::ostream& operator<<(std::ostream& stream, const MyString& str)
{
	stream << str.c_str();
	return stream;
}

}; // namespace
