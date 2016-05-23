#pragma once

#include <memory>

class MyString
{
  public:
	MyString();
	MyString(const MyString& that);
	MyString(const char* str);
	MyString& operator=(const MyString& that);

	MyString operator+(const MyString& that) const;
	
	bool empty() const;
	int size() const;

	bool operator==(const MyString& that) const;
	bool operator!=(const MyString& that) const;
	bool operator< (const MyString& that) const;

	const char& operator[](int index) const;
	char& operator[](int index);

	MyString& operator+=(const MyString& that);

	const char* c_str() const;

private:
	std::unique_ptr<char[]> mBuffer;
};
