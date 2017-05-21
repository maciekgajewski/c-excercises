#include <cstring>
#include <cassert>

template <typename T>
class TestClass
{
public:
    void test_const_char_constructor()
    {
        auto str = "this is string with length 29";
        auto s = T(str);
        assert(s == "this is string with length 29");
    }

    void test_move_constructor()
    {
        auto str = "this is string with length 29";
        auto s = T(str);
        auto s2 = std::move(s);
        assert (s2 == "this is string with length 29");
    }

    void test_copy_assignment()
    {
        auto s1 = T("blaah");
        T s2 = s1;

        assert (s2.length() == 5);
        assert (s1.length() == 5);
        assert (s1 == s2);
    }

    void test_move_assignment()
    {
        auto s1 = T("hello");
        auto s2 = T();
        s2= s1;
    }

    void test_assignment_from_c_str()
    {
        auto cstr = "hello";
        T str = cstr;
        assert(strcmp(str.c_str(), cstr) == 0);
    }

    void test_const_index_operator()
    {
        const T str = T("hello");
        const char c = str[1];
        assert (c == 'e');
    }

    void test_index_operatior()
    {
        auto str = T("hello");
        str[1] = 'E';
        assert (str == "hEllo");
    }

    void test_concat_operator()
    {
        auto s1 = T("Hello ");
        auto s2 = T("world!");

        auto s3 = s1 + s2;
        assert (s1 == "Hello ");
        assert (s2 == "world!");
        assert (s3 == "Hello world!");
    }

    void test_concat_same_string_operator()
    {
        auto s1 = T("Hello ");
        auto s2 = T("world!");

        s1 += s2;
        assert (s2 == "world!");
        assert (s1 == "Hello world!");
    }

    void test_c_srt()
    {
        auto s = T("string");
        auto cstr = s.c_str();

        assert (std::strcmp(cstr, "string") == 0);
    }

    void test_length()
    {
        auto str = "this is string with length 29";
        auto s = T(str);
        assert(s.length() == 29);
    }

    void test_size()
    {
        auto str = "this is string with length 29";
        auto s = T(str);
        assert(s.size() == 29);
    }
};

