#include "my_string.h"

#include <cstring>
#include <memory>

MyString::MyString(const MyString& that)
{
	if (!that.empty())
	{
		mBuffer = std::make_unique<char[]>(std::strlen(that.mBuffer.get()) + 1);
		std::strcpy(mBuffer.get(), that.mBuffer.get());
	}
}

MyString::MyString(MyString&& that)
{
	mBuffer = std::move(that.mBuffer);
}

MyString::MyString(const char* str)
{
	if (str != nullptr && str[0] != '\0')
	{
		mBuffer = std::make_unique<char[]>(std::strlen(str) + 1);
		std::strcpy(mBuffer.get(), str);
	}
}

MyString& MyString::operator=(const MyString& that)
{
	if (that.empty())
	{
		mBuffer.reset();
	}
	else
	{
		auto newBuffer = std::make_unique<char[]>(std::strlen(that.mBuffer.get()) + 1);
		std::strcpy(newBuffer.get(), that.mBuffer.get());

		mBuffer = std::move(newBuffer);
	}

	return *this;
}

MyString& MyString::operator=(MyString&& that)
{
	mBuffer = std::move(that.mBuffer);

	return *this;
}

MyString MyString::operator+(const MyString& that) const
{
	auto thisSize = size();
	auto thatSize = that.size();
	
	if (thatSize == 0)
	{
		return *this;
	}
	else if (thisSize == 0)
	{
		return that;
	}
	else
	{
		auto combinedBuffer = std::make_unique<char[]>(thisSize + thatSize + 1);

		std::strcpy(combinedBuffer.get(), mBuffer.get());
		std::strcpy(combinedBuffer.get() + thisSize, that.mBuffer.get());

		MyString result;
		result.mBuffer = std::move(combinedBuffer);

		return result;
	}
}

MyString& MyString::operator+=(const MyString& that)
{
	auto thatSize = that.size();
	
	if (thatSize == 0)
		return *this;
	
	if (mBuffer == nullptr)
	{
		mBuffer = std::make_unique<char[]>(thatSize + 1);
		std::strcpy(mBuffer.get(), that.mBuffer.get());
	}
	else
	{
		auto thisSize = size();

		auto combinedBuffer = std::make_unique<char[]>(thisSize + thatSize + 1);

		std::strcpy(combinedBuffer.get(), mBuffer.get());
		std::strcpy(combinedBuffer.get() + thisSize, that.mBuffer.get());

		mBuffer = std::move(combinedBuffer);
	}

	return *this;
}

bool MyString::empty() const
{
	return !mBuffer;
}

int MyString::size() const
{
	return empty() ? 0 : std::strlen(mBuffer.get());
}

bool MyString::operator==(const MyString& that) const
{
	return std::strcmp(c_str(), that.c_str()) == 0;
}

bool MyString::operator!=(const MyString& that) const
{
	return !operator==(that);
}

bool MyString::operator<(const MyString& that) const
{
	return std::strcmp(c_str(), that.c_str()) < 0;
}

const char& MyString::operator[](int index) const
{
	return mBuffer[index];
}

char& MyString::operator[](int index)
{
	return mBuffer[index];
}

const char* MyString::c_str() const
{
	return mBuffer ? mBuffer.get() : "";
}