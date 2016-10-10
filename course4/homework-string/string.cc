#include "string.hh"

namespace course {

string::string()
{
	mStr = std::make_unique<char[]>(1);
	mStr[0] = NULL;
	mStrSize = 0;
}

string::string(size_t n)
{
	mStr = std::make_unique<char[]>(n + 1);
	mStr[n] = NULL;
	mStrSize = n;
}

string::string(const char* s1)
{
	mStrSize = strlen(s1);
	mStr = std::make_unique<char[]>(mStrSize + 1);
	strcpy(mStr.get(), s1);
}

string::string(const string& s1)
{
	mStrSize = s1.mStrSize;
	mStr = std::make_unique<char[]>(mStrSize + 1);
	strcpy(mStr.get(), s1.c_str());
}

string::string(string&& s1)
{
	mStrSize = s1.length();
	mStr = std::move(s1.mStr);
}

bool string::empty() const
{
	return mStrSize == 0;
}

size_t string::length() const
{
	return mStrSize;
}

size_t string::size() const
{
	return mStrSize;
}

const char* string::c_str() const
{
	return mStr.get();
}

void string::clear()
{
	mStr = std::make_unique<char[]>(1);
	mStr[0] = NULL;	
	mStrSize = 0;
}

bool string::operator== (const string& str) const
{
	return (mStrSize == str.mStrSize) && (strcmp(mStr.get(), str.c_str()) == 0);
}

bool string::operator != (const string& str) const
{
	return !(*this == str);
}

string& string::operator= (const string& str)
{
	mStrSize = str.mStrSize;
	mStr = std::make_unique<char[]>(mStrSize + 1);
	strcpy(mStr.get(), str.c_str());
	return *this;
}

char string::operator[] (size_t n) const
{
	if (n < mStrSize)
	{
		return mStr[n];
	}
	else
	{
		throw std::runtime_error("index exceeds string size");
	}
}

char& string::operator[] (size_t n)
{
	if (n < mStrSize)
	{
		return mStr[n];
	}
	else
	{
		throw std::runtime_error("index exceeds string size");
	}
}

string string::operator+ (const string& str1) const
{
	string str(mStrSize + str1.length());
	strcpy(str.mStr.get(), mStr.get());
	strcat(str.mStr.get() + mStrSize, str1.c_str());
	return str;
}

string& string::operator+= (const string& str)
{
	*this = *this + str;
	return *this;
}

bool operator< (const string& str1, const string& str2)
{
	return strcmp(str1.c_str(), str2.c_str()) < 0;
}

std::ostream& operator<< (std::ostream& os, const string& str)
{
	os << str.c_str();
	return os;
}
}
