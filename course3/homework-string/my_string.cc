#include "my_string.h"
# include <iostream>

MyString::MyString(){
};

MyString::MyString(const char* inchar){
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
	if (data == nullptr)
		return 0;
	else
		return std::strlen(data.get());
};

bool operator==(const MyString &s1, const MyString &s2){
	return std::strcmp(s1.c_str(), s2.c_str()) == 0;
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

const char* MyString::c_str() const{
	if (data ==nullptr)
		return "";
	else
		return data.get();
}


MyString::MyString(MyString &&other){
	data = std::move(other.data);
}

MyString& MyString::operator=(MyString&& other){	
	data = std::move(other.data);
	return *this;
}

MyString& MyString::operator=(const MyString& other){	
	data.reset(new char[other.size()+1]);
	std::strcpy(data.get(), other.c_str());
	return *this;
}

MyString operator+(const MyString& s1, const MyString &s2)
{
	MyString new_str;
	int n_total = s1.size() + s2.size();
	if(n_total > 0){
		new_str.data = std::unique_ptr<char[]>(new char[n_total + 1]);
		std::strcpy(new_str.data.get(), s1.c_str());
		std::strcat(new_str.data.get(), s2.c_str());	
	}
	return new_str;
}


MyString& MyString::operator+=(const MyString& s2){
	MyString new_str= *this + s2;
	data = std::move(new_str.data);
	return *this;
}

bool MyString::operator<(const MyString& s2){
	return std::strcmp(this->c_str(), s2.c_str()) < 0;
}

