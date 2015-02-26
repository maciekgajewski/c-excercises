#pragma once

#include <ostream>
#include <memory>


class String
{
public:
	
	//////////////////////////
	// Sub-types
	
	// Every good behaving container should define 'value_type' type, which is the type of elements stored within
	using value_type = char;
	
	// Iterator types
	
	// feel free to use different types for iterators
	using iterator = char*;
	using const_iterator = const char*;
	
	//////////////////////////
	// Creation / Destruction
	
	// Default constructor, creates empty string.
	// Should be cheap and perform no memory allocation
	String();
	
	// Destructor should free all allocated memory
	~String();
	
	// Performs deep-copy of another string
	String(const String& o);
	
	// Moves content from another string
	String(String&& o);
	
	// Initializes string with the content of c-string.
	// Assumes 's' is not null.
	// I repeat: ASSUMES 's' IS NOT NULL. Do not check if s is null. You may use 'assert', but that's it.
	String(const char* s);
	
	// Initializes string with a range (described by a pair of iterators).
	// Allows for initializing with a content of another container containing characters (or compatible type)
	template<typename It>
	String(It first, It last);
	
	///////////////////////
	// State querying
	
	// Returns length of the string, in characters.
	std::size_t size() const;
	
	// Returns 'true' is string is empty, 'false' otherwise.
	// If empty() => true, then size() => 0
	// If empty() => false, then size() => >0
	bool empty() const;
	
	// Returns a pointer to null-terminated character array, usable in C functions.
	// The pointer may only be valid until the string is destroyed or modified.
	const char* c_str() const;
	
	// returns a character at specified position in the string.
	// Assumes pos < size()
	char operator[](std::size_t pos) const; 
	
	// returns a reference to a character at specified position in the string.
	// Assumes pos < size()
	char& operator[](std::size_t pos);

	//////////////////////
	// Range base access
	
	// Returns writable iterator to the beginning of sequence.
	// In case of empty string, returns the same value as end()
	iterator begin();
	
	// Returns past-the end iterator.
	iterator end();
	
	// Returns read-only iterator to the beginning of the sequence.
	// For empty string, returns the same as end() const
	const_iterator begin() const;
	
	// Returns read-only past-the end iterator.
	const_iterator end() const;
	
	
	///////////////////////
	// Modifying operations
	
	// Clears any content.
	// After calling: empty() => true, size() => 0
	void clear();
	
	// Swaps content with another instance.
	// Should be fast, O(1) operation.
	void swap(String& other);
	
	// Assigns content of another string
	// returns *this
	String& operator = (const String& s);
	
	// Assigns content of C-string.
	// Assumes s is not null
	// returns *this
	String& operator = (const char* s);
	
	// Moves away content from another rvalue instance
	String& operator = (String&& s);
	

	////////////////////////
	// Comparison
	
	// Compares with another string
	bool operator==(const String& s) const;
	
	// Compares with c-string. Assumes s is not null
	bool operator==(const char* s) const;

private:
	std::unique_ptr<value_type[] > mValue;
	std::size_t mSize = 0;
};

// Other operators

// Concatenates strings
String operator + (const String& a, const String& b);

// Stream output operator
std::ostream& operator<<(std::ostream& stream, const String& s);

