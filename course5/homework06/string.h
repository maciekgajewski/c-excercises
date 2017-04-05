#include<memory>
#include<iostream>

class String
{
public:
    String();
    String(const String& src);
    String& operator= (const String& src);
    String(String&& src);
    String& operator= (String&& src);

    String(const char* src);
    String& operator= (const char* src);

    int length() const;     //the latter const means no change to *this object
    char& operator[] (int i);
    const char& operator[] (int i) const;

    String operator+ (const String& src) const;
    String operator+ (const char* src) const;
    String& operator+= (const String& src);
    String& operator+= (const char* src);
    const char* c_str() const;

    bool operator== (const String& src);
    bool operator!= (const String& src);
    bool operator== (const std::string& src);
    bool operator!= (const std::string& src);
    bool operator== (const char* src);
    bool operator!= (const char* src);

private:
    std::unique_ptr<char[]> charbuffer;
    int size;

};

std::ostream& operator<< (std::ostream& stream, const String& src);
