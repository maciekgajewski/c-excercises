#include <iostream>
#include <cstring>
#include "my_string.h"

MyString::MyString(){
	buffer = std::unique_ptr<char[]>(new char[1]);
	buffer[0] = '\0';
}

MyString::MyString(const char* theString){
	buffer = std::unique_ptr<char[]>(new char[std::strlen(theString) + 1]);
	unsigned int i;
	for (i = 0; i < std::strlen(theString); i++){
			buffer[i] = theString[i];
	}
	buffer[i] = '\0';
}

MyString::MyString(const MyString& theString){
	buffer = std::unique_ptr<char[]>(new char[theString.size() + 1]);
	unsigned int i;
	for (i = 0; i < std::strlen(theString.buffer.get()); i++){
		buffer[i] = theString[i];
	}
	buffer[i] = '\0';
}
   
const bool MyString::empty() const {
	if (buffer){
		return buffer[0] == '\0' ;
	}
	else return true;
}

const size_t MyString::size() const {
	if (buffer){
		return std::strlen(buffer.get());
	}
	else return 0;
}	

const char* MyString::c_str() const {
	if (buffer){
		return buffer.get();
	}
	else return '\0';
}

const bool MyString::operator == (const MyString& theString) const {
	if (buffer && theString.buffer){
		return std::strcmp(buffer.get(), theString.buffer.get()) == 0 ;
	}
	else if ( buffer == nullptr && theString.buffer == nullptr ){
		return true;
	}
	else return false;
}

const bool MyString::operator != (const MyString& theString) const{
	if ( buffer && theString.buffer){
		if ( *this == theString ){
			return false;
		}
		else return true;
	}
	else if ( buffer == nullptr && theString.buffer == nullptr ){
		return false;
	}
	else return false;
}

MyString& MyString::operator = (const MyString& theString) { 
	if (theString.empty()){
        	buffer = std::unique_ptr<char[]>(new char[1]);
		buffer[0] = '\0';
	}
	else{
        	buffer = std::unique_ptr<char[]>(new char[theString.size()+1]);
		std::strcpy(buffer.get(), theString.buffer.get());
	}
	return *this;
}


MyString MyString::operator + (const MyString& theString) const {
	MyString newString; 
	if (theString.empty()){
		std::strcpy(newString.buffer.get(), buffer.get());
	}
	else{
        	newString.buffer = std::unique_ptr<char[]>(new char[size() + theString.size() + 1]);
		std::strcpy(newString.buffer.get(), buffer.get());
		std::strcat(newString.buffer.get(), theString.buffer.get());
	}
	return newString;
}

MyString& MyString::operator += (const MyString& theString){ 
	 *this = *this + theString;
	 return *this;
}

char& MyString::operator[](int index) const{
	return buffer[index]; 
}
