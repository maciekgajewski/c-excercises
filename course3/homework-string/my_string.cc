#include "my_string.h"
#include <cstring>
#include <stdexcept>

MyString::MyString(const char* str) : buf(std::make_unique<char[]>(std::strlen(str)+1)) {
	std::strcpy(buf.get(), str);
}

MyString::MyString(const MyString& obj) : buf(std::make_unique<char[]>(obj.size()+1)) {
	if (obj.buf)
		std::strcpy(buf.get(), obj.buf.get());
}

bool MyString::operator==(const MyString& rhs) const {
	// This is a logical xor
	if (!rhs.buf != !buf)
		return false;
	if (!rhs.buf && !buf)
		return true;
	return std::strcmp(buf.get(), rhs.buf.get()) == 0;
}

bool MyString::operator!=(const MyString& rhs) const {
	return !operator==(rhs);
}

bool MyString::operator>(const MyString& rhs) const{
	if (!buf || !rhs.buf)
		return false;
	return strcmp(buf.get(), rhs.buf.get()) > 0;
}

bool MyString::operator>=(const MyString& rhs) const{
	if (!buf || !rhs.buf)
		return false;
	return strcmp(buf.get(), rhs.buf.get()) >= 0;
}

bool MyString::operator<(const MyString& rhs) const{
	if (!buf || !rhs.buf)
		return false;
	return !operator>=(rhs);
}

bool MyString::operator<=(const MyString& rhs) const{
	if (!buf || !rhs.buf)
		return false;
	return !operator>(rhs);
}

const char& MyString::operator[](unsigned int i) const {
	return buf.get()[i];
}

const char& MyString::at(unsigned int i) const {
	if (!buf)
		throw std::range_error("Trying to index unallocated buffer.");
	if (i >= size())
		throw std::range_error("Trying to access outside allocated buffer.");
	return operator[](i);
}

char& MyString::operator[](unsigned int i) {
	return buf.get()[i];
}

char& MyString::at(unsigned int i) {
	if (!buf)
		throw std::range_error("Trying to index unallocated buffer.");
	if (i >= size())
		throw std::range_error("Trying to access outside allocated buffer.");
	return operator[](i);
}

MyString MyString::operator+(const MyString& rhs) const {
	if (!buf && !rhs.buf)
		return MyString();
	auto concat_string = std::make_unique<char[]>(size() + rhs.size() + 1);
	if (buf)
		std::strcpy(concat_string.get(), buf.get());
	if (buf && rhs.buf)
		std::strcat(concat_string.get(), rhs.buf.get());
	if (!buf && rhs.buf)
		std::strcpy(concat_string.get(), rhs.buf.get());
	return MyString(concat_string.get());
}

void MyString::operator=(const MyString& rhs) {
	buf.reset();
	if (rhs.buf) {
		buf = std::make_unique<char[]>(rhs.size()+1);
		std::strcpy(buf.get(), rhs.buf.get());
	}
}

void MyString::operator+=(const MyString& rhs) {
	if (rhs.buf) {
		auto concat_string = std::make_unique<char[]>(size() + rhs.size() + 1);
		if (buf) {
			std::strcpy(concat_string.get(), buf.get());
			std::strcat(concat_string.get(), rhs.buf.get());
		}
		else {
			std::strcpy(concat_string.get(), rhs.buf.get());
		}
		buf = std::make_unique<char[]>(size() + rhs.size() + 1);
		std::strcpy(buf.get(), concat_string.get());
	}
}

bool MyString::empty() const {
	if (!buf)
		return true;
	return buf[0] == 0;
}

size_t MyString::size() const {
	if (!buf)
		return 0;
	return std::strlen(buf.get());
}

const char* MyString::c_str() const {
	if (!buf)
		return "";
	return buf.get();
}
