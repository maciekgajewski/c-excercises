#pragma once
#include <memory>
#include <string.h>
#include <stdexcept>
#include <iostream>

namespace course {

class string
{
private:
	std::unique_ptr<char[]> mStr;
	size_t mStrSize;

public:
	string();
	string(size_t n);
	string(const char* s1);
	string(const string& s1);
	string(string&& s1);
	bool empty() const;
	size_t length() const;
	size_t size() const;
	const char* c_str() const;
	void clear();
	bool operator== (const string& str) const;
	bool operator!= (const string& str) const;
	string& operator= (const string& str);
	string& operator+= (const string& str);
	char operator[] (size_t n) const;
	char& operator[] (size_t n);
	string operator+ (const string& str1) const;

	friend bool operator< (const string& str1, const string& str2);
	friend std::ostream& operator<< (std::ostream& os, const string& str);
};

}