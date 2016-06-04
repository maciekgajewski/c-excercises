#include "my_string.h"
# include <iostream>

MyString::MyString(){};

MyString::MyString(const char* inchar){
	std::cout << "string literal constructor called";
	int n = std::strlen(inchar) + 1;
	data = std::unique_ptr<char[]>(new char[n]);
 	std::strcpy(data.get(), inchar);
};

MyString::MyString(const MyString& that): data(new char[that.size()+1]){
	std::strcpy(data.get(), that.data.get());
}


bool MyString::empty() const{
	return size() == 0;
};

int MyString::size() const{
	if (data == 0)
		return 0;
	else
		return std::strlen(data.get());
};

bool operator==(const MyString &s1, const MyString &s2){
//	std::cout << "comparison operator " << s1.data.get()<< "==" << s2.data.get() << "?" << std::endl;
	return std::strcmp(s1.data.get(), s2.data.get()) == 0;
}

bool operator!=(const MyString &s1, const MyString &s2){
	return !(s1==s2);
}

char& MyString::operator[](const int i){
	return data.get()[i];
}

char MyString::operator[](const int i) const{
	return data.get()[i];
}

char* MyString::c_str() const{
	char* cstr = new char[size()+1];
	std::strcpy(cstr,data.get());
	return cstr;
}


MyString::MyString(MyString &&other){
	data = std::move(other.data);
}

MyString& MyString::operator=(MyString&& other){
	data = std::move(other.data);
	return *this;
}
