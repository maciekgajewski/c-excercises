#include "str.h"

namespace mstr
{
    Str::Str(const Str& str1, const Str& str2)
    {
        int size1 = str1.size();
        int size2 = str2.size();

        start = new char[size1 + size2 + 1];

        std::strcpy(start, str1.start);
        std::strcpy(start + size1, str2.start);

        mid = end = start + size1 + size2 + 1;
    }

    void Str::Assign(const char* s, int size)
    {
        if (size > capacity())
        {
            Str temp(s);
            swap(temp);
        }
        else
        {
            mid = start + size + 1;
            std::strcpy(start, s);
        }
    }

    void Str::Initialize(const char* s)
    {
        int size = std::strlen(s) + 1;

        start = new char[size];
        std::strcpy(start, s);

        mid = end = start + size;
    }

    std::ostream &operator<<(std::ostream &os, const Str& str)
    {
        std::copy(str.start, str.start + str.size(), std::ostream_iterator<char>(os));
        return os;
    }

    void swap(Str& str1, Str& str2)
    {
        str1.swap(str2);
    }
}

