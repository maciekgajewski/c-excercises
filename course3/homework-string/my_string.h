#pragma once
#include <memory>
#include <cstring>

class MyString
{
	// TODO

	public:
		MyString();

		MyString(const char* theString);

		MyString(const MyString& theString);

		const bool empty() const;

		const size_t size() const;	
		
		const char* c_str() const;	

		const bool operator == (const MyString& theString) const;

		const bool operator != (const MyString& theString) const;

		char& operator[](int index) const;
		
		MyString& operator=(const MyString& theString);
		
		MyString operator+(const MyString& theString) const;
		
		MyString& operator+=(const MyString& theString);
		

	private:

	std::unique_ptr<char[]> buffer;
};
