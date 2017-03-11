#pragma once

#include <cstring>
#include <memory>
#include <iostream>

class MyString
{
public:
	// default ctor
	MyString() : mSize(0) {
	}
	// string literal ctor
	MyString(const char* other) {
		mSize = std::strlen(other);
		mBuffer = std::make_unique<char[]>(mSize);
		std::strcpy(mBuffer.get(), other);
	}
	// copy ctor
	MyString(const MyString& other) {
		mSize = other.mSize;
		mBuffer = std::make_unique<char[]>(mSize);
		std::strcpy(mBuffer.get(), other.mBuffer.get());
	}
	// move ctor
	MyString(MyString&& other) {
		mSize = other.mSize;
		mBuffer = std::move(other.mBuffer);
	}
	bool empty() const { 
		return mSize == 0; 
	}
	std::size_t size() const { 
		return mSize;
	}
	const char* c_str() const { 
		return mBuffer.get();
	}
	MyString& operator=(const MyString& other) { 
		mSize = other.mSize;
		if (mSize == 0) {
			mBuffer.reset();
		}
		else{
			mBuffer = std::make_unique<char[]>(mSize);
			std::strcpy(mBuffer.get(), other.mBuffer.get());
		}
		return *this; 
	}
	bool operator==(const MyString& other) const {
		return size() == other.size()
			&& std::strncmp(mBuffer.get(), other.mBuffer.get(), size()) == 0;
	}
	bool operator!=(const MyString& other) const { 
		return !(*this == other);
	}
	char operator[](int i) const { 
		return mBuffer[i]; 
	}
	char& operator[](int i) { 
		return mBuffer[i];
	}
	MyString operator+(const MyString& other) const { 
		MyString str;
		str.mSize = size() + other.size();
		if (str.size() == 0) {
			return str;
		}
		str.mBuffer = std::make_unique<char[]>(str.size());
		if (size() > 0) {
			std::strcat(str.mBuffer.get(), mBuffer.get());
		}
		if (other.size() > 0) {
			std::strcat(str.mBuffer.get(), other.mBuffer.get());
		}
		return str;
	}
	MyString& operator+=(const MyString& other) { 
		std::size_t new_size = size() + other.size();
		if (new_size == 0) {
			mBuffer.reset();
		}
		else {
			std::unique_ptr<char[]> buf = std::make_unique<char[]>(new_size);
			if (size() > 0) {
				std::strcat(buf.get(), mBuffer.get());
			}
			if (other.size() > 0) {
				std::strcat(buf.get(), other.mBuffer.get());
			}
			mBuffer = std::move(buf);
		}
		mSize = new_size;
		return *this;
	}
	bool operator<(const MyString& other) const { 
		if (size() > other.size()) {
			return false;
		}
		if (size() == other.size()) {
			return std::strncmp(mBuffer.get(), other.mBuffer.get(), size()) < 0;
		}
		return true;
	}
private:
	std::unique_ptr<char[]> mBuffer;
	std::size_t mSize;
};

std::ostream& operator<<(std::ostream& out, const MyString& str) {
	return out << str.c_str();
}
