#include "my_string.h"
#include "my_unique_ptr.h"
#include <cstring>
#include <stdexcept>

//MyString::MyString(const char* str) : buf(std::make_unique<char[]>(std::strlen(str)+1)) {
MyString::MyString(const char* str) : buf(MyMakeUnique<char[]>((int)(std::strlen(str)+1))) {
	std::strcpy(buf.get(), str);
}

//MyString::MyString(const MyString& obj) : buf(std::make_unique<char[]>(obj.size()+1)) {
MyString::MyString(const MyString& obj) : buf(MyMakeUnique<char[]>((int)(obj.size()+1))) {
	//if (obj.buf)
	if (!obj.empty())
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
	//if (rhs.buf) {
	if (!rhs.empty()) {
		//buf = std::make_unique<char[]>(rhs.size()+1);
		buf = MyMakeUnique<char[]>((int)(rhs.size()+1));
		std::strcpy(buf.get(), rhs.buf.get());
	}
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs) {
	//if (rhs.buf) {
	if (!rhs.empty()) {
		//auto concat_string = std::make_unique<char[]>(size() + rhs.size() + 1);
		auto concat_string = MyMakeUnique<char[]>((int)(size() + rhs.size() + 1));
		//if (buf) {
		if (!empty()) {
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
	//if (!rhs.buf != !buf)
	if (rhs.empty() != empty())
		return false;
	if (rhs.empty() && empty())
	//if (!rhs.buf && !buf)
		return true;
	return std::strcmp(buf.get(), rhs.buf.get()) == 0;
}

bool MyString::operator!=(const MyString& rhs) const {
	return !operator==(rhs);
}

bool MyString::operator>(const MyString& rhs) const{
	//if (!buf)
	if (empty())
		return false;
	//if (!rhs.buf)
	if (rhs.empty())
		return true;
	return strcmp(buf.get(), rhs.buf.get()) > 0;
}

bool MyString::operator>=(const MyString& rhs) const{
	//if (!buf)
	if (empty())
		return false;
	//if (!rhs.buf)
	if (rhs.empty())
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
	//if (!buf)
	if (empty())
		throw std::range_error("Trying to index unallocated buffer.");
	if (i >= size())
		throw std::range_error("Trying to access outside allocated buffer.");
	return operator[](i);
}

char& MyString::operator[](unsigned int i) {
	return buf.get()[i];
}

char& MyString::at(unsigned int i) {
	//if (!buf)
	if (empty())
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
	//if (!buf)
	if (buf.get() == nullptr)
	//if (buf.get())
		return true;
	return buf[0] == 0;
}

size_t MyString::size() const {
	//if (!buf)
	if (empty())
		return 0;
	return std::strlen(buf.get());
}

const char* MyString::c_str() const {
	//if (!buf)
	if (empty())
		return "";
	return buf.get();
}
