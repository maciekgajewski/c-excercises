#include <cstdio>
#include <string>
#include <tuple>

void print_impl(int val)
{
    std::printf("%i\n", val);
}

void print_impl(double val)
{
    std::printf("%g\n", val);
}

void print_impl(const std::tuple<double, int>& val)
{
    std::printf("%.*f\n", std::get<1>(val), std::get<0>(val));
}

void print_impl(bool val)
{
    std::printf("%s\n", val ? "true": "false");
}

void print_impl(std::string val)
{
    std::printf("%s\n", val.c_str());
}

void print_impl(const char* val)
{
    std::printf("%s\n", val);
}

void print()
{ }

template<typename T, typename... Types>
void print(T val, Types... rest)
{
    print_impl(val);
    print(rest...);
}

int main()
{
	// comment indicates the expected input
	std::string s = "world!";
	float f = 6;
	print(7, true, std::make_tuple(1.0/3.0, 2), "hello, ", s, f);
}

