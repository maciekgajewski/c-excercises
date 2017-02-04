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

MyString::MyString(MyString&& obj) {
	buf = std::move(obj.buf);
}

MyString& MyString::operator=(MyString&& rhs) {
	buf = std::move(rhs.buf);
	return *this;
}

MyString& MyString::operator=(const MyString& rhs) {
	buf.reset();
	if (rhs.buf) {
		buf = std::make_unique<char[]>(rhs.size()+1);
		std::strcpy(buf.get(), rhs.buf.get());
	}
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs) {
	if (rhs.buf) {
		auto concat_string = std::make_unique<char[]>(size() + rhs.size() + 1);
		if (buf) {
			std::strcpy(concat_string.get(), buf.get());
			std::strcat(concat_string.get(), rhs.buf.get());
		}
		else {
			std::strcpy(concat_string.get(), rhs.buf.get());
		}
		buf = std::move(concat_string);
	}
	return *this;
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
	if (!buf)
		return false;
	if (!rhs.buf)
		return true;
	return strcmp(buf.get(), rhs.buf.get()) > 0;
}

bool MyString::operator>=(const MyString& rhs) const{
	if (!buf)
		return false;
	if (!rhs.buf)
		return true;
	return strcmp(buf.get(), rhs.buf.get()) >= 0;
}

bool MyString::operator<(const MyString& rhs) const{
	return !operator>=(rhs);
}

bool MyString::operator<=(const MyString& rhs) const{
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
	MyString result(*this);
	return result+=rhs;
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
