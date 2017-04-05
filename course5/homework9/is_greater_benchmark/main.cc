
#include <benchmark/benchmark_api.h>

#include <iostream>
#include <string>
#include <cstring>

volatile bool result;

bool is_greater_string(const std::string& a, const std::string& b)
{
	return a > b;
}

bool is_greater_char(const char* a, const char* b)
{
	return std::strcmp(a, b) > 0;
}

void BM_is_greater_strings(benchmark::State& state)
{
	size_t stringSize = state.range(0);
	std::string a(stringSize, '0');
	std::string b(stringSize, '0');
	b[stringSize - 1] = '1';

	while (state.KeepRunning())
		result |= is_greater_string(a.c_str(), b.c_str());
}

void BM_is_greater_char_arrays(benchmark::State& state)
{
	size_t stringSize = state.range(0);
	std::string a(stringSize, '0');
	std::string b(stringSize, '0');
	a[stringSize - 1] = '1';

	while (state.KeepRunning())
		result |= is_greater_char(a.c_str(), b.c_str());
}

BENCHMARK(BM_is_greater_strings)->RangeMultiplier(2)->Range(1, 1 << 20);

// On my machine the char_arrays method is 5 times faster than the strings
// method for 1 byte strings, but for 1MB strings it is 15 times faster
BENCHMARK(BM_is_greater_char_arrays)->RangeMultiplier(2)->Range(1, 1 << 20);

BENCHMARK_MAIN()
