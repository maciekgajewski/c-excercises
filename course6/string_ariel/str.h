#pragma once

#include <iostream>
#include <cstring>

class Str
{
public:
    Str()
    {
        start = mid = end = nullptr;
    }

    Str(const char* s)
    {
        int size = std::strlen(s);
        start = new char[size];
        end = start;

        while (*s != '\0')
        {
            *end++ = *s++;
        }

        mid = end;
    }

    Str(const Str& str)
    {
        int size = str.Size();
        start = new char[size];
        end = start;

        for (int i = 0; i < size; i++)
        {
            *end++ = str[i];
        }

        mid = end;
    }

    Str(Str&& str) :start(str.start), mid(str.mid), end(str.end)
    {
        str.start = str.mid = str.end = nullptr;
    }

    ~Str()
    {
        Dispose();
    }

    char operator[](int i) const
    {
        return *(start + i);
    }

    char& operator[](int i)
    {
        return *(start + i);
    }

    Str& operator = (const Str& str)
    {
        if (str.Size() > Capacity())
        {
            Str temp(str);
            Swap(*this, temp);
        }
        else
        {
            mid = start + str.Size();
            Copy(str);
        }

        return *this;
    }

    Str& operator = (const char* s)
    {
        int size = std::strlen(s);
        if (size > Capacity())
        {
            Str temp(s);
            Swap(*this, temp);
        }
        else
        {
            mid = start + size;
            Copy(s);
        }

        return *this;
    }

    Str operator + (const Str& rh)
    {
        return Str(*this, rh);
    }

    Str& operator += (const Str& rh)
    {
        if(rh.Size() + Size() <= Capacity())
        {
            for(int i = 0; i < rh.Size(); i++)
            {
                *mid++ = rh[i];
            }
        }
        else
        {
            Str temp = *this + rh;
            Swap(*this, temp);
        }

        return *this;
    }

    int Size() const
    {
        return mid - start;
    }

    int Capacity() const
    {
        return end - start;
    }

    friend std::ostream &operator<<(std::ostream &os, const Str& str);

private:
    char* start, *end, *mid;

    Str(const Str& str1, const Str& str2)
    {
        int size1 = str1.Size();
        int size2 = str2.Size();

        start = new char[size1 + size2];
        end = start;

        for (int i = 0; i < size1; i++)
        {
            *end++ = str1[i];
        }

        for (int i = 0; i < size2; i++)
        {
            *end++ = str2[i];
        }

        mid = end;
    }

    friend void Swap(Str& str1, Str& str2)
    {
        std::swap(str1.start, str2.start);
        std::swap(str1.mid, str2.mid);
        std::swap(str1.end, str2.end);
    }

    void Dispose()
    {
        delete[] start;
    }

    void Copy(const char* s)
    {
        char* index = start;
        while (*s != '\0')
        {
            *index++ = *s++;
        }
    }

    void Copy(const Str& str)
    {
        char* index = start;
        for (int i = 0; i < Size(); i++)
        {
            *index++ = str[i];
        }
    }
};

std::ostream &operator<<(std::ostream &os, const Str& str) {
    char* index = str.start;
    while (index != str.mid)
    {
        os << *index++;
    }

    return os;
}
