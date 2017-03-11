#pragma once
#include <iostream>
#include <memory>
#include <string>

namespace simple_string
{

class String
{
public:
    String();

private:
    std::unique_ptr<char[]> buffer;

}; // String

} // namespace

// std::ostream& operator<<(std::ostream& s, const String);
