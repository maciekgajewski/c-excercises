#include "ustring.h"
#include "tuple_pretty_print.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <tuple>
#include <algorithm>

template <typename StringClass>
struct ctor_def
{
    static std::string name() { return "ctor_def"; }
    auto operator() (const char*, size_t)
    {
        StringClass str;
        return std::make_tuple(
                str.empty(),
                str.length(),
                std::string(str.data()), // string content till closing zero at the end
                std::string(str.data(), str.length()) // string content
            );
    }
};

template <typename StringClass>
struct ctor_char
{
    static std::string name() { return "ctor_char"; }
    auto operator() (const char *initStr, size_t)
    {
        StringClass str(initStr);
        return std::make_tuple(
                std::strlen(initStr) == str.length(),
                str.length(),
                std::string(str.data()), // string content till closing zero at the end
                std::string(str.data(), str.length()) // string content
            );
    }
};

template <typename StringClass>
struct ctor_char_size
{
    static std::string name() { return "ctor_char_size"; }
    auto operator() (const char *initStr, size_t length)
    {
        StringClass str(initStr, length);
        return std::make_tuple(
                length == str.length(),
                str.length(),
                std::string(str.data()), // string content till closing zero at the end
                std::string(str.data(), str.length()) // string content
            );
    }
};

template <typename StringClass>
struct ctor_copy
{
    static std::string name() { return "ctor_copy"; }
    auto operator() (const char *initStr, size_t length)
    {
        std::unique_ptr<StringClass> str = std::make_unique<StringClass>(initStr, length);
        StringClass strCopy = *str;
        bool dataPtrDifferent = str->data() != strCopy.data();
        bool sizeSame = str->size() == strCopy.size();
        // delete original string
        str = nullptr;
        return std::make_tuple(dataPtrDifferent, sizeSame,
                std::string(strCopy.data()), // string content till closing zero at the end
                std::string(strCopy.data(), strCopy.length()) // string content
            );
    }
};

template <typename StringClass>
struct ctor_move
{
    static std::string name() { return "ctor_move"; }
    auto operator() (const char *initStr, size_t length)
    {
        StringClass str(initStr, length);
        StringClass str2 = std::move(str);
        return std::make_tuple(
                str.data() != str2.data(), // data pointer should be different
                str.data() != nullptr,
                str.size(),
                str2.size(),
                std::string(str2.data()), // string content till closing zero at the end
                std::string(str2.data(), str2.length()) // string content
            );
    }
};


template <typename StringClass>
struct assignment_char
{
    static std::string name() { return "assignment_char"; }
    auto operator() (const char *initStr, size_t)
    {
        StringClass str;
        str = initStr;
        return std::make_tuple(
                std::strlen(initStr) == str.length(),
                str.length(),
                std::string(str.data()), // string content till closing zero at the end
                std::string(str.data(), str.length()) // string content
            );
    }
};

template <typename StringClass>
struct copy_assignment
{
    static std::string name() { return "copy_assignment"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str;
        StringClass str2(initStr, size);
        str = str2;
        return std::make_tuple(
                std::strlen(initStr) == str.length(),
                str.length(),
                std::string(str.data()), // string content till closing zero at the end
                std::string(str.data(), str.length()) // string content
            );
    }
};

template <typename StringClass>
struct move_assignment
{
    static std::string name() { return "move_assignment"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str;
        StringClass str2(initStr, size);
        str = std::move(str2);
        return std::make_tuple(
                size == str.length(),
                str2.length() == 0,
                str2.data() != nullptr,
                std::string(str2.data()),
                std::string(str2.data(), str2.length()),
                str.length(),
                std::string(str.data()), // string content till closing zero at the end
                std::string(str.data(), str.length()) // string content
            );
    }
};

template <typename StringClass>
struct operator_at
{
    static std::string name() { return "operator_at"; }
    auto operator() (const char *initStr, size_t size)
    {
        const StringClass str(initStr, size);
        return std::make_tuple(
                size > 0 ? str[0] : '#',
                size > 3 ? str[3] : '#',
                size > 10 ? str[10] : '#',
                size > 20 ? str[20] : '#',
                size > 60 ? str[60] : '#',
                size > 0 ? str[str.length()-1] : '#'
            );
    }
};

template <typename StringClass>
struct operator_at_write
{
    static std::string name() { return "operator_at_write"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        if (size > 0) str[0] = '#';
        if (size > 3) str[3] = '#';
        if (size > 21) str[21] = '#';
        if (size > 32) str[32] = '#';
        if (size > 65) str[65] = '#';
        if (size > 0) str[str.length()-1] = '#';
        return std::make_tuple(
                std::string(str.data()), // string content till closing zero at the end
                std::string(str.data(), str.length()) // string content
            );
    }
};

template <typename StringClass>
struct at_over_index_access
{
    static std::string name() { return "at_over_index_access"; }
    auto operator() (const char *initStr, size_t size)
    {
        const StringClass str(initStr, size);
        char c1 = '#';
        bool got_exception1 = false;
        try
        {
            c1 = str.at(str.length());
        }
        catch (const std::out_of_range &e)
        {
            got_exception1 = true;
        }
        char c2 = '#';
        bool got_exception2 = false;
        try
        {
            c2 = str.at(str.length()+1);
        }
        catch (const std::out_of_range &e)
        {
            got_exception2 = true;
        }

        return std::make_tuple(
                got_exception1, c1,
                got_exception2, c2
            );
    }
};

template <typename StringClass>
struct at_over_index_write
{
    static std::string name() { return "at_over_index_write"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        bool got_exception1 = false;
        try
        {
            str.at(str.length()) = 'C';
        }
        catch (const std::out_of_range &e)
        {
            got_exception1 = true;
        }
        bool got_exception2 = false;
        try
        {
            str.at(str.length()+1) = 'C';
        }
        catch (const std::out_of_range &e)
        {
            got_exception2 = true;
        }
        return std::make_tuple(
                got_exception1,
                got_exception2,
                std::string(str.data()), // string content till closing zero at the end
                std::string(str.data(), str.length()) // string content
            );
    }
};

template <typename StringClass>
struct front_access
{
    static std::string name() { return "front_access"; }
    char operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        return str.front();
    }
};

template <typename StringClass>
struct back_access
{
    static std::string name() { return "back_access"; }
    char operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        return str.back();
    }
};

template <typename StringClass>
struct front_back_as_ref
{
    static std::string name() { return "front_back_as_ref"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        std::string out;
        std::copy(&str.front(), &str.back()+1, std::back_inserter(out));
        return out;
    }
};

template <typename StringClass>
struct data_and_size
{
    static std::string name() { return "data_and_size"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        return std::make_tuple(
                str.size(),
                str.length(),
                std::string(str.data(), str.size())
            );
    }
};

template <typename StringClass>
struct const_data_and_size
{
    static std::string name() { return "const_data_and_size"; }
    auto operator() (const char *initStr, size_t size)
    {
        const StringClass str(initStr, size);
        return std::make_tuple(
                str.size(),
                str.length(),
                std::string(str.data(), str.size())
            );
    }
};

template <typename StringClass>
struct c_str_method
{
    static std::string name() { return "c_str_method"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        return std::string(str.c_str());
    }
};

template <typename StringClass>
struct empty_string
{
    static std::string name() { return "empty_string"; }
    auto operator() (const char*, size_t)
    {
        StringClass str;
        return std::make_tuple(
                str.empty(),
                str.length(),
                std::string(str.c_str())
            );
    }
};

template <typename StringClass>
struct empty_after_clear
{
    static std::string name() { return "empty_after_clear"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        str.clear();
        return std::make_tuple(
                str.empty(),
                str.length(),
                std::string(str.c_str())
            );
    }
};

template <typename StringClass>
struct length_method
{
    static std::string name() { return "length_method"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        return str.length();
    }
};

template <typename StringClass>
struct operator_plus_equal_char
{
    static std::string name() { return "operator_plus_equal_char"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        for (int i=0; i<200; ++i)
            str += 'm';
        return std::string(str.data(), str.length());
    }
};

template <typename StringClass>
struct operator_plus_equal_cstring
{
    static std::string name() { return "operator_plus_equal_cstring"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        for (int i=0; i<20; ++i)
            str += "Mokus";
        return std::string(str.data(), str.length());
    }
};

template <typename StringClass>
struct operator_plus_equal_string
{
    static std::string name() { return "operator_plus_equal_string"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        for (int i=0; i<20; ++i)
            str += StringClass("Mokus");
        return std::string(str.data(), str.length());
    }
};

template <typename StringClass>
struct operator_plus_char
{
    static std::string name() { return "operator_plus_char"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        for (int i=0; i<200; ++i)
        {
            str = 'm' + str;
            str = str + 'm';
        }
        return std::string(str.data(), str.length());
    }
};

template <typename StringClass>
struct operator_plus_char_nul
{
    static std::string name() { return "operator_plus_char"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        for (int i=0; i<200; ++i)
        {
            str = '\0' + str;
            str = str + '\0';
        }
        return std::string(str.data(), str.length());
    }
};

template <typename StringClass>
struct operator_plus_cstring
{
    static std::string name() { return "operator_plus_cstring"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        for (int i=0; i<200; ++i)
        {
            str = "Mokus" + str;
            str = str + "Macska";
        }
        return std::string(str.data(), str.length());
    }
};

template <typename StringClass>
struct operator_plus_string
{
    static std::string name() { return "operator_plus_string"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        for (int i=0; i<200; ++i)
        {
            str = StringClass("Mokus") + str;
            str = str + StringClass("Macska");
        }
        return std::string(str.data(), str.length());
    }
};

template <typename StringClass>
struct operator_plus_string_with_nul
{
    static std::string name() { return "operator_plus_string_with_nul"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        for (int i=0; i<200; ++i)
        {
            str = StringClass("Mo\0kus", 6) + str;
            str = str + StringClass("Mac\0ska", 6);
        }
        return std::string(str.data(), str.length());
    }
};

template <typename StringClass>
struct push_back
{
    static std::string name() { return "push_back"; }
    std::string operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        for (int i=0; i<200; ++i)
            str.push_back('m');
        return std::string(str.data(), str.length());
    }
};

template <typename StringClass>
struct to_stream
{
    static std::string name() { return "to_stream"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass inputStr(initStr, size);
        std::ostringstream os;
        os << inputStr;
        std::string str = os.str();
        return std::make_tuple(
                std::string(str.data()), // string content till closing zero at the end
                std::string(str.data(), str.length()) // string content
            );
    }
};

template <typename StringClass>
struct resize_method
{
    static std::string name() { return "resize_method"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        str.resize(std::min<size_t>(64ul, size));
        str.shrink_to_fit();
        return std::make_tuple(
                str.empty(),
                str.length(),
                std::string(str.c_str())
            );
    }
};

template <typename StringClass>
struct resize_method_short
{
    static std::string name() { return "resize_method_short"; }
    auto operator() (const char *initStr, size_t size)
    {
        StringClass str(initStr, size);
        str.resize(std::min<size_t>(16ul, size));
        str.shrink_to_fit();
        return std::make_tuple(
                str.empty(),
                str.length(),
                std::string(str.c_str())
            );
    }
};

auto testStrings = {
    std::make_tuple("", 0),
    std::make_tuple("A", 1),
    std::make_tuple("AB", 2),
    std::make_tuple("ABC", 3),
    std::make_tuple("abcd", 4),
    std::make_tuple("Mokus", 5),
    std::make_tuple("Macska", 6),
    std::make_tuple("Macs\0ka", 7),
    std::make_tuple(u8"A kis mókus felmászott a fára és sok mogyorót talált, amit elrejtett, hogy legyen mit ennie a télen.", 107)
};

template < template <typename> class TestFunc>
void compare_test()
{
    std::string test_name = TestFunc<std::string>::name();
    bool failed = false;
    for (auto test : testStrings)
    {
        auto lhs = std::apply(TestFunc<std::string>(), test);
        auto rhs = std::apply(TestFunc<Course::String>(), test);
        if (lhs != rhs)
        {
            if (!failed)
                std::cout << test_name << " [FAILED]\n";
            failed = true;
            std::cout << "\tstd::string result: '" << lhs << "'\n";
            std::cout << "\tString result:      '" << rhs << "'\n";
        }
    }
    if (!failed)
    {
        std::cout << "Test " << test_name << " [OK]\n";
    }
}

int main()
{
    compare_test<ctor_def>();
    compare_test<ctor_char>();
    compare_test<ctor_char_size>();
    compare_test<ctor_copy>();
    compare_test<ctor_move>();
    compare_test<assignment_char>();
    compare_test<copy_assignment>();
    compare_test<move_assignment>();
    compare_test<operator_at>();
    compare_test<operator_at_write>();
    compare_test<at_over_index_access>();
    compare_test<at_over_index_write>();
    compare_test<front_access>();
    compare_test<back_access>();
    compare_test<front_back_as_ref>();
    compare_test<data_and_size>();
    compare_test<const_data_and_size>();
    compare_test<c_str_method>();
    compare_test<empty_string>();
    compare_test<empty_after_clear>();
    compare_test<length_method>();
    compare_test<operator_plus_equal_char>();
    compare_test<operator_plus_equal_cstring>();
    compare_test<operator_plus_equal_string>();
    compare_test<operator_plus_char>();
    compare_test<operator_plus_char_nul>();
    compare_test<operator_plus_cstring>();
    compare_test<operator_plus_string>();
    compare_test<operator_plus_string_with_nul>();
    compare_test<push_back>();
    compare_test<to_stream>();
    compare_test<resize_method>();
    compare_test<resize_method_short>();
    // XXX iterators
    // XXX reserve, capacity, shrink_to_fit
    // XXX pop_back
    // XXX resize (2 variants)
}
