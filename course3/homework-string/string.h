#pragma once

#include <memory>


namespace Karun
{
	
class String
{

public:
	String() = default;
	String(const char* str);
	String(const String& str);
	String(String&& str);

	bool empty() const;
	std::size_t size() const;
	const char* c_str() const;
	int compare(const String& str) const;
	
	using iterator = char*;
	using const_iterator = const char*;
	
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	
	String& operator=(const String& str);
	String& operator=(String&& str);
	bool operator==(const String& str) const;
	bool operator!=(const String& str) const;
	bool operator<(const String& str) const;
	const char& operator[](int idx) const;
	char& operator[](int idx);
	String operator+(const String& str) const;
	String& operator+=(const String& str);

private:
	std::unique_ptr<char[]> mBuffer;

};

}

namespace std
{

template<>
struct hash<Karun::String>
{
	std::size_t operator()(const Karun::String& str) const;
};

}
