#pragma once
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>

class MyString
{
	// TODO
private:
	std::unique_ptr<char[]> mStr; 
	size_t mStrSize;

public:
	MyString();
	MyString(const char* s1);
	MyString(const MyString& s1);
	MyString(MyString&& s1);
	bool operator== (const MyString& str) const;
	bool operator != (const MyString& str) const;
	MyString& operator= (const MyString& str);
	MyString& operator+= (const MyString& str);
	char& operator[] (size_t n) const;
	bool empty() const;
	size_t size() const;
	const char* c_str() const;
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

MyString::MyString(const char* s1)
{
	mStrSize = strlen(s1);
	mStr = std::make_unique<char[]>(mStrSize + 1);
	for (size_t i = 0; i < mStrSize; i++)
	{
		mStr[i] = s1[i];
	}
	mStr[mStrSize] = NULL;
}

MyString::MyString(const MyString& s1)
{
	mStrSize = s1.mStrSize;
	mStr.reset();
	mStr = std::make_unique<char[]>(mStrSize + 1);
	for (size_t i = 0; i < mStrSize; i++)
	{
		mStr[i] = s1.mStr[i];
	}
	mStr[mStrSize] = NULL;
}

MyString::MyString(MyString&& s1)
{
	mStrSize = s1.size();
	mStr = std::move(s1.mStr);
}

bool MyString::operator== (const MyString& str) const
{
	if (mStrSize != str.mStrSize)
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < mStrSize; i++)
		{
			if (mStr[i] != str.mStr[i])
			{
				return false;
			}
		}
	}
	return true;
}

bool MyString::operator != (const MyString& str) const
{
	return !(*this == str);
}

MyString& MyString::operator= (const MyString& str)
{
	mStrSize = str.mStrSize;
	mStr.reset();
	mStr = std::make_unique<char[]>(mStrSize + 1);
	for (size_t i = 0; i < mStrSize; i++)
	{
		mStr[i] = str[i];
	}
	mStr[mStrSize] = NULL;
	return *this;
}

MyString& MyString::operator+= (const MyString& str)
{
	*this = *this + str;
	return *this;
}

char& MyString::operator[] (size_t n) const
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

MyString operator+ (const MyString& str1, const MyString& str2)
{
	MyString str;
	str.mStrSize = str1.mStrSize + str2.mStrSize;
	str.mStr = std::make_unique<char[]>(str.mStrSize + 1);
	for (size_t i = 0; i < str1.mStrSize; i++)
	{
		str.mStr[i] = str1[i];
	}
	for (size_t i = 0; i < str2.mStrSize; i++)
	{
		str.mStr[str1.mStrSize + i] = str2[i];
	}
	str.mStr[str.mStrSize] = NULL;
	return str;
}

bool operator< (const MyString& str1, const MyString& str2)
{
	size_t m = std::min(str1.size(), str2.size());
	for (size_t i = 0; i < m; i++)
	{
		if (str1[i] == str2[i])
		{
			continue;
		}
		else
		{
			return str1[i] < str2[i];
		}
	}
	return str1.size() < str2.size();
}

std::ostream& operator<< (std::ostream os, const MyString& str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		os << str[i];
	}
	return os;
}