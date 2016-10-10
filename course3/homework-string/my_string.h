#pragma once
#include <memory>
#include <string.h>
#include <stdexcept>
#include <iostream>

class MyString
{
	// TODO
private:
	std::unique_ptr<char[]> mStr; 
	size_t mStrSize;

public:
	MyString();
	MyString(size_t n);
	MyString(const char* s1);
	MyString(const MyString& s1);
	MyString(MyString&& s1);
	bool empty() const;
	size_t size() const;
	const char* c_str() const;
	bool operator== (const MyString& str) const;
	bool operator != (const MyString& str) const;
	MyString& operator= (const MyString& str);
	MyString& operator+= (const MyString& str);
	char operator[] (size_t n) const;
	char& operator[] (size_t n);
	friend MyString operator+ (const MyString& str1, const MyString& str2);
	friend bool operator< (const MyString& str1, const MyString& str2);
	friend std::ostream& operator<< (std::ostream os, const MyString& str);
};

MyString::MyString()
{
	mStr = std::make_unique<char[]>(1);
	mStr[0] = NULL;
	mStrSize = 0;
}

MyString::MyString(size_t n)
{
	mStr = std::make_unique<char[]>(n + 1);
	mStr[n] = NULL;
	mStrSize = n;
}

MyString::MyString(const char* s1)
{
	mStrSize = strlen(s1);
	mStr = std::make_unique<char[]>(mStrSize + 1);
	strcpy(mStr.get(), s1);
}

MyString::MyString(const MyString& s1)
{
	mStrSize = s1.mStrSize;
	mStr = std::make_unique<char[]>(mStrSize + 1);
	strcpy(mStr.get(), s1.c_str());
}

MyString::MyString(MyString&& s1)
{
	mStrSize = s1.size();
	mStr = std::move(s1.mStr);
}

bool MyString::empty() const
{
	return mStrSize == 0;
}

size_t MyString::size() const
{
	return mStrSize;
}

const char* MyString::c_str() const
{
	return mStr.get();
}

bool MyString::operator== (const MyString& str) const
{
	return (mStrSize == str.mStrSize) && (strcmp(mStr.get(), str.c_str()) == 0);
}

bool MyString::operator != (const MyString& str) const
{
	return !(*this == str);
}

MyString& MyString::operator= (const MyString& str)
{
	mStrSize = str.mStrSize;
	mStr = std::make_unique<char[]>(mStrSize + 1);
	strcpy(mStr.get(), str.c_str());
	return *this;
}

char MyString::operator[] (size_t n) const
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

char& MyString::operator[] (size_t n)
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

MyString operator+ (const MyString& str1, const MyString& str2)
{
	MyString str(str1.mStrSize + str2.mStrSize);
	strcpy(str.mStr.get(), str1.c_str());
	strcat(str.mStr.get() + str1.size(), str2.c_str());
	return str;
}

MyString& MyString::operator+= (const MyString& str)
{
	*this = *this + str;
	return *this;
}

bool operator< (const MyString& str1, const MyString& str2)
{
	return strcmp(str1.c_str(), str2.c_str()) < 0;
}

std::ostream& operator<< (std::ostream os, const MyString& str)
{
	os << str.c_str();
	return os;
}