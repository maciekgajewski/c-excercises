#include "mystr.h"
#include <memory>
#include <cmath> 
#include <cstring>

using namespace mystring;


// Function to create a new unique pointer, memset it and initialize it with a 
// new string. 
// Repeatedly needed for copy/move assignment and construction
void MyString::Reset_mStr(int len, const char* str)
{
	mStr = std::make_unique<char[]>(len+1); // add 1 for \0 termination
	std::strncpy(mStr.get(), str, len);
	mStr[len] = '\0';
}

MyString::MyString(const MyString& str)  // copy constructor
{
	Reset_mStr(str.length(), str.c_str());
}

MyString& MyString::operator = (const MyString& str)  // copy assignment
{
	Reset_mStr(str.length(), str.c_str());
	return *this;
}
	

MyString:: MyString(MyString&& str)  // move constructor
{
	mStr = std::move(str.mStr);
}

MyString& MyString::operator = (MyString&& str)  // move assignment
{
	mStr = std::move(str.mStr);
	return *this;
}

MyString::MyString(const char* str) // User defined constructor
{
	Reset_mStr(std::strlen(str), str);
}

MyString& MyString::operator = (const char* str)
{
	Reset_mStr(std::strlen(str), str);
	return *this;
}

	
char& MyString::operator[] (const size_t index) 
{
	if (index < this->length())
		return mStr.get()[index];

	throw std::range_error ("Index out of bound"); 

}

const char& MyString::operator[] (const size_t index) const
{
	if (index < this->length())
		return mStr.get()[index];

	throw std::range_error ("Index out of bound"); 
}

MyString  MyString::operator+ (const MyString& str) // concatenation
{
	MyString new_str(mStr.get());
	new_str += str;
	return new_str;
}

MyString&  MyString::operator+= (const MyString& str) // concatenation assignment
{
	// Create a new string of enuogh length (by adding both), initialize by concatenating and
	// then move to the current objectś mStr variable

	int new_size = str.length() + this->length();
	std::unique_ptr<char[]> new_str = std::make_unique<char[]>(new_size +1 );
	std::strcpy(new_str.get(), this->c_str());
	std::strcat(new_str.get(), str.c_str());
	new_str.get()[new_size+1] = '\0';
	mStr = std::move(new_str);
	return *this;
}

bool MyString::operator == (const MyString& str)
{
	if (this->length() == 0 && str.length() == 0)
		return true;

	return strcmp(mStr.get(), str.mStr.get()) == 0;
}

bool MyString::operator == (const char* str)
{
	if (this->length() == 0 && strlen(str) == 0)
		return true;

	return strcmp(mStr.get(), str) == 0;
}

bool MyString::operator != (const MyString& str)
{
	return !(*this == str);
}

bool MyString::operator != (const char* str)
{
	return strcmp(mStr.get(), str) != 0;

}

const char* MyString::c_str() const
{
	return mStr.get();
}

unsigned int MyString::length() const
{
	if (mStr.get() == nullptr)
		return 0;

	return std::strlen(mStr.get());
}
