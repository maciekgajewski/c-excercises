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
    String(const char*);

    void Print() const;
    int Length() const;

private:
    std::unique_ptr<char[]> buffer = nullptr;
    int size = 0;

}; // String

} // namespace
