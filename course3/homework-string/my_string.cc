#include "my_string.h"
#include <cstring>
#include <stdexcept>

MyString::MyString(const char* str) : buf(std::make_unique<char[]>(std::strlen(str)+1)) {
	std::strcpy(buf.get(), str);
}

MyString::MyString(const MyString& obj) : buf(std::make_unique<char[]>(obj.size()+1)) {
	std::strcpy(buf.get(), obj.buf.get());
}

bool MyString::operator==(const MyString& rhs) const {
	if (!rhs.buf xor !buf)
		return false;
	if (!rhs.buf and !buf)
		return true;
	return std::strcmp(buf.get(), rhs.buf.get()) == 0;
}

bool MyString::operator!=(const MyString& rhs) const {
	return !operator==(rhs);
}

const char& MyString::operator[](int i) const {
	if (!buf)
		throw std::range_error("Trying to index unallocated buffer.");
	return buf.get()[i];
}

char& MyString::operator[](int i) {
	if (!buf)
		throw std::range_error("Trying to index unallocated buffer.");
	return buf.get()[i];
}

MyString MyString::operator+(const MyString& rhs) const {
	auto concat_string = std::make_unique<char[]>(size() + rhs.size() + 1);
	std::strcpy(concat_string.get(), buf.get());
	std::strcat(concat_string.get(), rhs.buf.get());
	return MyString(concat_string.get());
}

void MyString::operator=(const MyString& rhs) {
	buf.release();
	if (rhs.buf) {
		buf = std::make_unique<char[]>(rhs.size()+1);
		std::strcpy(buf.get(), rhs.buf.get());
	}
	return;
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
