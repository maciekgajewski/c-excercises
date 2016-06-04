#pragma once
#include <memory>
#include <iostream>
#include <cstring>

class MyString
{
private:
    std::unique_ptr<char[]> data;
public:
	MyString();  			// default constructor
	MyString(const char*);		// string literal constructor
	MyString(const MyString&);	// copy constructor	

	bool empty() const;
	int size() const;

	friend bool operator== (const MyString &s1, const MyString &s2); // equality operator is friended
	friend bool operator!=  (const MyString &s1, const MyString &s2);
	char& operator[](const int); // indexing operator
	char operator[](const int) const; // const indexing operator

	char* c_str() const; // c_string method?

	MyString(MyString&&);
	MyString& operator=(MyString&&);
};



