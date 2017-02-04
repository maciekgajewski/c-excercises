#include <iostream>
#include <cstring>
#include "my_string.h"

MyString::MyString(){
	buffer = std::unique_ptr<char[]>(new char[1]);
	buffer = '\0';
}

MyString::MyString(const char* theString){
	buffer = std::unique_ptr<char[]>(new char[std::strlen(theString) + 1]);
	int i;
	for (i = 0; i < std::strlen(theString); i++){
			buffer[i] = theString[i];
	}
	buffer[i] = '\0';
}

MyString::MyString(const MyString& theString){
	buffer = std::unique_ptr<char[]>(new char[theString.size() + 1]);
	int i;
	for (i = 0; i < std::strlen(theString.buffer.get()); i++){
		buffer[i] = theString[i];
	}
	buffer[i] = '\0';
}
   
bool MyString::empty() const {
	if (buffer){
		return buffer[0] == '\0' ? true : false ;
	}
	return true;
}

size_t MyString::size() const {
	if (buffer){
		return std::strlen(buffer.get());
	}
	else return 0;
}	

const bool MyString::operator == (const MyString& theString){
	if (buffer && theString.buffer){
		return std::strcmp(buffer.get(), theString.buffer.get()) == 0 ? true : false ;
	}
	else if ( buffer == nullptr && theString.buffer == nullptr ){
		return true;
	}
	else return false;
}

const bool MyString::operator != (const MyString& theString){
	if ( buffer && theString.buffer){
		return std::strcmp(buffer.get(), theString.buffer.get()) == 0 ? false : true ;
	}
	else if ( buffer == nullptr && theString.buffer == nullptr ){
		return false;
	}
	else return false;
}

char& MyString::operator[](int index) const{
	return buffer[index]; 
}
