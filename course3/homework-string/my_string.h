#pragma once

#include <memory>

class MyString
{
  public:
	MyString();
	MyString(const MyString& that);
	MyString(const char* str);
	
	bool empty() const;
	int size() const;

	bool operator==(const MyString& that) const;
	bool operator!=(const MyString& that) const;
	const char& operator[](int index) const;
	char& operator[](int index);

private:
	MyString(const char* source, const int length);

	int mLength;
	std::unique_ptr<char[]> mBuffer;
};
