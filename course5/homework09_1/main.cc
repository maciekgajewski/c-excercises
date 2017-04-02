/*
Homework 1

Use google benchmark to compare the performance of these two functions:

bool is_greater(const std::string& a, const std::string& b) { return a > b; }
bool is_greater(const char* a, const char* b) { return std::strcmp(a, b) > 0; }

in a context when they are both called with const char* parameters. Test different length of the input string, from 1 char to 1MB (or even longer, if you so fancy or if results are interesting).
Be mindful on what you’re measuring!
*/
#include <benchmark/benchmark.h>
#include <string>

using namespace std::literals;

template<typename T>
bool is_greater(const T& a, const T& b)
{
    return a > b;
}

template<>
bool is_greater(const char* const& a, const char* const& b)
{
    return std::strcmp(a, b) > 0;
}

static void string_bench(benchmark::State& state)
{
	while(state.KeepRunning())
	{
        std::string input = "a";
        const char * input_cstr = input.c_str();
		for(auto i = 0; i < 1000000; i += 1)
        {
            benchmark::DoNotOptimize(is_greater<std::string>(input_cstr, input_cstr));
            input += "a";
            input_cstr = input.c_str();
        }
	}
}

static void const_char_star_bench(benchmark::State& state)
{
	while(state.KeepRunning())
    {
        std::string input = "a";
        const char * input_cstr = input.c_str();
		for(auto i = 0; i < 1000000; i += 1)
        {
            benchmark::DoNotOptimize(is_greater<const char *>(input_cstr, input_cstr));
            input += "a";
            input_cstr = input.c_str();
        }
    }
}

BENCHMARK(string_bench);
BENCHMARK(const_char_star_bench);

BENCHMARK_MAIN();
