#ifndef STRING_H
#define STRING_H
#include <memory>
#include <ostream>


class String
{
public:
    String() = default;
    String(String &&);
    String(char* data);
    String(const String& data);

    String operator = (const String& string);
    String operator = (String && string);
    String operator = (const char* data);

    ~String();

    char operator [](std::size_t index);
    char operator [] (std::size_t index) const;

    String operator + (const String& string);

    String operator +=(const String& string);

    char * c_str();

    int Length() const;
private:
    std::unique_ptr<char[]> buffer = nullptr;
};

std::ostream& operator << (std::ostream& stream, const String& string);

#endif // STRING_H
