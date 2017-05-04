#include<benchmark/benchmark.h>
#include<cstring>
#include<string>
#include<iostream>

/*
Run on (2 X 3504.06 MHz CPU s)
		2017-05-04 15:37:55
		--------------------------------------------------------------------
		Benchmark                             Time           CPU Iterations
		--------------------------------------------------------------------
		BM_is_greater_string/1               93 ns         93 ns    7515006
		BM_is_greater_string/8              105 ns        105 ns    6647822
		BM_is_greater_string/64             103 ns        103 ns    6719034
		BM_is_greater_string/512            162 ns        162 ns    4337274
		BM_is_greater_string/4096           407 ns        407 ns    1710907
		BM_is_greater_string/32768         3424 ns       3394 ns     196920
		BM_is_greater_string/262144      170073 ns     158562 ns       4610
		BM_is_greater_string/1048576     783139 ns     776885 ns        843
		BM_is_greater_char/1                  9 ns          9 ns   73391348
		BM_is_greater_char/8                  9 ns          9 ns   74076815
		BM_is_greater_char/64                10 ns         10 ns   69932105
		BM_is_greater_char/512                9 ns          9 ns   73954533
		BM_is_greater_char/4096               9 ns          9 ns   72910124
		BM_is_greater_char/32768              9 ns          9 ns   75937333
		BM_is_greater_char/262144             9 ns          9 ns   74535524
		BM_is_greater_char/1048576            9 ns          9 ns   75308215
*/
bool is_greater_string(const std::string& a, const std::string& b)
{
    return a > b;
}

bool is_greater_char(const char* a, const char* b)
{
    return std::strcmp(a,b) > 0;
}


static void BM_is_greater_string(benchmark::State& state)
{
    std::string a(state.range(0), 'z');
    std::string b(state.range(0), 'a');
    while (state.KeepRunning())
        benchmark::DoNotOptimize(is_greater_string(a.c_str(), b.c_str()));
}

static void BM_is_greater_char(benchmark::State& state)
{
    std::string a(state.range(0), 'z');
    std::string b(state.range(0), 'a');
    while (state.KeepRunning())
        benchmark::DoNotOptimize(is_greater_char(a.c_str(), b.c_str()));
}

BENCHMARK(BM_is_greater_string)->Range(1, 1<<20);
BENCHMARK(BM_is_greater_char)->Range(1, 1<<20);

BENCHMARK_MAIN();
