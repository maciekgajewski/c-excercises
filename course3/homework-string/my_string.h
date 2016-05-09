#pragma once

#include <string>

class MyString
{
private:
	std::unique_ptr<char[]> mBuffer;

public:
	MyString(): mBuffer(new char[1]) {}

	MyString(const char* str)
	{
		mBuffer = std::unique_ptr<char[]>(new char[std::strlen(str)]); // can I make this more concise?
		std::strcpy(mBuffer.get(), str);
	}

	MyString(const MyString& str)
	{
		mBuffer = std::unique_ptr<char[]>(new char[str.size()]);
		std::strcpy(mBuffer.get(), str.mBuffer.get());
	}

	bool empty() const
	{
		return size() == 0;
	}

	int size() const
	{
		return std::strlen(mBuffer.get());
	}

	bool operator==(const char* str) const
	{
		return std::strcmp(mBuffer.get(), str) == 0;
	}

	bool operator==(const MyString& str) const
	{
		return std::strcmp(mBuffer.get(), str.mBuffer.get()) == 0;
	}

	bool operator!=(const char* str) const
	{
		return !operator==(str);
	}

	bool operator!=(const MyString& str) const
	{
		return !operator==(str);
	}

	const char& operator[](const int idx) const
	{
		return mBuffer.get()[idx];
	}

	char& operator[](const int idx)
	{
		return mBuffer.get()[idx];
	}
	
};
