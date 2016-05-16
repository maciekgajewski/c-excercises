#pragma once
#include <memory>

class MyString
{
	// TODO

	public:
		MyString();

		MyString(const char* theString);

		MyString(const MyString& theString);

		bool empty() const;

		size_t size() const;	

		const bool operator == (const MyString& theString);

		const bool operator != (const MyString& theString);

		char& operator[](int index) const;

	private:

	std::unique_ptr<char[]> buffer;
};
