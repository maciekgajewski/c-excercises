#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <tuple>
#include <cerrno>

class StringView
{
public:
    StringView(const char *str, size_t length=std::string::npos)
        : mData(str)
        , mLength(length == std::string::npos ? std::strlen(str) : length)
    {}
    StringView(const std::string &str, size_t length=std::string::npos)
        : mData(str.data())
        , mLength(length == std::string::npos ? str.length() : length)
    {}

    StringView slice(size_t offset, size_t length=std::string::npos) const
    {
        assert(length == std::string::npos ? offset < mLength : offset+length < mLength);
        return StringView(mData+offset, length == std::string::npos ? std::string::npos : length-offset);
    }

    char operator[](size_t pos) const
    {
        assert(pos < mLength);
        return mData[pos];
    }
    const char* data() const { return mData; }
    size_t length() const { return mLength; }
private:
    const char *mData = nullptr;
    size_t mLength = 0;
};

class PrintError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
    PrintError() : std::runtime_error(std::strerror(errno))
    {}
};

void print(int i)
{
    if (std::printf("%d", i) < 0) throw PrintError();
}

void print(bool b)
{
    if (std::printf(b ? "true" : "false") < 0) throw PrintError();
}

void print(double d)
{
    if (std::printf("%lg", d) < 0) throw PrintError();
}

void print(double d, unsigned precision)
{
    if (std::printf("%.*lf", precision, d) < 0) throw PrintError();
}

void print(const char *str)
{
    if (std::printf("%s", str) < 0) throw PrintError();
}

void print(const std::string &s)
{
    if (std::printf("%s", s.c_str()) < 0) throw PrintError();
}

void print(const StringView &str)
{
    auto result = std::fwrite(str.data(), sizeof(char), str.length(), stdout);
    if (result != str.length() && ferror(stdout)) throw PrintError("Failed to write to stdout");
}


constexpr size_t count_params_in_format_str(const char *format, size_t count=0);
constexpr size_t count_params_in_format_str_in_bracket(const char *format, size_t count=0)
{
    return format[0] == '\0' ? count : (
        format[0] == '{' ? count_params_in_format_str_in_bracket(format+1, count) : (
        format[0] == '}' ? count_params_in_format_str(format+1, count+1) :
        count_params_in_format_str(format+1, count)));
}

constexpr size_t count_params_in_format_str(const char *format, size_t count)
{
    return format[0] == '\0' ? count : (
        format[0] == '{' ? count_params_in_format_str_in_bracket(format+1, count) :
        count_params_in_format_str(format+1, count));
}

void fprint_impl(const StringView &format)
{
    print(format);
}

template <typename FirstParam, typename ...Params>
void fprint_impl(const StringView &format, FirstParam firstParam, Params ...params)
{
    bool hadBracket = false;
    size_t pos = 0;
    while (pos < format.length())
    {
        if (hadBracket)
        {
            if (format[pos] == '{')
                hadBracket = true;
        }
        else
        {
            if (format[pos] == '}')
            {
                print(format.slice(0, pos-1));
                print(firstParam);
                fprint_impl(format.slice(pos+1), params...);
                return;
            }
            if (format[pos] != '{')
                hadBracket = false;
        }
        ++pos;
    }
}

#define fprint(format, ...) \
    static_assert(count_params_in_format_str(format) == std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value, "Number of arguments does not match format string!"); \
    fprint_impl(format, __VA_ARGS__);

int main()
{
    fprint("Mokus {} macska {} mosomedve {} sundiszno {}\n", 42, "42\n", 42.34, true);
}
