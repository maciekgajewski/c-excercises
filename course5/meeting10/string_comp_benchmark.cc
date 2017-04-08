#include <benchmark/benchmark.h>

#include <string>
#include <cstring>

bool is_greater_string(const std::string& a, const std::string& b) { return a>b; }
bool is_greater(const char* a, const char* b) { return std::strcmp(a, b) > 0;}

static void is_greater_bench(benchmark::State& state)
{
	std::string a(state.range(0), 'a');
	std::string z(state.range(0), 'z');
	
	while(state.KeepRunning())
		benchmark::DoNotOptimize( is_greater(a.c_str(), z.c_str()));
}

static void is_greater_bench_nocstr(benchmark::State& state)
{
	std::string a(state.range(0), 'a');
	std::string z(state.range(0), 'z');
	
	const char* acs = a.c_str();
	const char* zcs = z.c_str();
	
	while(state.KeepRunning())
		benchmark::DoNotOptimize( is_greater(acs, zcs));
}
static void is_greater_string_bench(benchmark::State& state)
{
	std::string a(state.range(0), 'a');
	std::string z(state.range(0), 'z');
	
	while(state.KeepRunning())
		benchmark::DoNotOptimize( is_greater_string(a.c_str(), z.c_str()));
}


BENCHMARK(is_greater_bench)->Range(1, 1<<20);
BENCHMARK(is_greater_bench_nocstr)->Range(1, 1<<20);
BENCHMARK(is_greater_string_bench)->Range(1, 1<<20);
BENCHMARK_MAIN();