#include "string.hh"

#include <cstring>
#include <iostream>
#include <memory>

namespace course {

// char* ctor
string::string(const char* other) {
	mSize = std::strlen(other);
	mBuffer = std::make_unique<char[]>(mSize + 1);
	std::strcpy(mBuffer.get(), other);
}

// copy ctor
string::string(const string& other) {
	mSize = other.mSize;
	mBuffer = std::make_unique<char[]>(mSize + 1);
	std::strcpy(mBuffer.get(), other.mBuffer.get());
}

// move ctor
string::string(string&& other) {
	mSize = other.mSize;
	mBuffer = std::move(other.mBuffer);
	other.mBuffer.reset();
}



bool string::empty() const {
	return mSize == 0;
}

std::size_t string::size() const {
	return mSize;
}
std::size_t string::length() const {
	return mSize;
}
void string::clear() {
	if (mSize == 0) return;
	mSize = 0;
	mBuffer.reset();
}

const char* string::c_str() const {
	if (mSize > 0) {
		return mBuffer.get();
	}
	else {
		return "";
	}
}



string& string::operator=(const string& other) {
	mSize = other.mSize;
	mBuffer = std::make_unique<char[]>(mSize + 1);
	std::strcpy(mBuffer.get(), other.mBuffer.get());
	return *this;
}

bool string::operator==(const string& other) const {
	return 
		mSize == other.mSize &&
		std::strncmp(mBuffer.get(), other.mBuffer.get(), mSize + 1) == 0;
}

bool string::operator!=(const string& other) const {
	return !(*this == other);
}

bool string::operator<(const string& other) const {
	if (mSize > other.mSize) {
		return false;
	}
	if (mSize == other.mSize) {
		return std::strncmp(mBuffer.get(), other.mBuffer.get(), mSize + 1) < 0;
	}
	return true;
}

char string::operator[](int i) const {
	return mBuffer[i];
}

char& string::operator[](int i) {
	return mBuffer[i];
}

string string::operator+(const string& other) const {
	string str(*this);
	str += other;
	return str;
}

string& string::operator+=(const string& other) {
	if (other.mSize == 0) {
		return *this;
	}

	if (mSize == 0) {
		mBuffer = std::make_unique<char[]>(other.mSize + 1);
		std::strcpy(mBuffer.get(), other.mBuffer.get());
	}
	else {
		std::unique_ptr<char[]> buf = std::make_unique<char[]>(mSize + other.mSize + 1);
		std::strcpy(buf.get(), mBuffer.get());
		std::strcat(buf.get(), other.mBuffer.get());
		mBuffer.swap(buf);
	}
	mSize += other.mSize;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const string& str) {
	return out << str.c_str();
}

}
