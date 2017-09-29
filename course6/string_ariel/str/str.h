#pragma once

#include <iostream>
#include <cstring>
#include <iterator>

namespace mstr
{
    class Str
    {
    public:
        Str()
        {
            start = mid = end = nullptr;
        }

        Str(const char* s)
        {
            Initialize(s);
        }

        Str(const Str& str)
        {
            Initialize(str.start);
        }

        Str(Str&& str) : start(str.start), mid(str.mid), end(str.end)
        {
            str.start = str.mid = str.end = nullptr;
        }

        ~Str()
        {
            delete[] start;
        }

        char operator[](int i) const
        {
            return start[i];
        }

        char& operator[](int i)
        {
            return start[i];
        }

        Str& operator = (const Str& str)
        {
            Assign(str.start, str.size());

            return *this;
        }

        Str& operator = (const char* s)
        {
            Assign(s, std::strlen(s));

            return *this;
        }

        Str operator + (const Str& rh)
        {
            return Str(*this, rh);
        }

        Str& operator += (const Str& rh)
        {
            Assign((*this + rh).start, this->size() + rh.size());

            return *this;
        }

        int size() const
        {
            return mid - start - 1;
        }

        int capacity() const
        {
            return end - start - 1;
        }

        void swap(Str& str)
        {
            std::swap(start, str.start);
            std::swap(mid, str.mid);
            std::swap(end, str.end);
        }

        char* c_str()
        {
            return start;
        }

        friend std::ostream &operator<<(std::ostream &os, const Str& str);

    private:
        char* start, *end, *mid;

        Str(const Str& str1, const Str& str2);

        void Initialize(const char* s);

        void Assign(const char* s, int size);
    };
}
