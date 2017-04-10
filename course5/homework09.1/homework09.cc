#include <string>
#include <cstring>
#include <iostream>

#include <benchmark/benchmark.h>

//   Run on (4 X 3301 MHz CPU s)
//   2017-04-10 22:57:33
//   ------------------------------------------------------------------------------
//   Benchmark                                       Time           CPU Iterations
//   ------------------------------------------------------------------------------
//   is_greater_stdstring_loop_same/1               60 ns         60 ns   11499675
//   is_greater_stdstring_loop_same/8               63 ns         63 ns   10976420
//   is_greater_stdstring_loop_same/64              77 ns         76 ns    9093245
//   is_greater_stdstring_loop_same/512            120 ns        120 ns    5811469
//   is_greater_stdstring_loop_same/4096           394 ns        394 ns    1780761
//   is_greater_stdstring_loop_same/32768         3655 ns       3655 ns     193084
//   is_greater_stdstring_loop_same/262144      106027 ns     106029 ns       6362
//   is_greater_stdstring_loop_same/1048576     531511 ns     531516 ns       1210
//   is_greater_cstring_loop_same/1                  2 ns          2 ns  280860181
//   is_greater_cstring_loop_same/8                  2 ns          2 ns  280022318
//   is_greater_cstring_loop_same/64                 8 ns          8 ns   87087187
//   is_greater_cstring_loop_same/512               20 ns         20 ns   34620421
//   is_greater_cstring_loop_same/4096             138 ns        138 ns    5039238
//   is_greater_cstring_loop_same/32768           1230 ns       1230 ns     565205
//   is_greater_cstring_loop_same/262144         10539 ns      10539 ns      65937
//   is_greater_cstring_loop_same/1048576        43397 ns      43398 ns      16222
//   is_greater_stdstring_loop/1                    62 ns         62 ns   11152248
//   is_greater_stdstring_loop/8                    66 ns         66 ns   10556762
//   is_greater_stdstring_loop/64                   73 ns         73 ns    9463994
//   is_greater_stdstring_loop/512                 100 ns        100 ns    6905232
//   is_greater_stdstring_loop/4096                303 ns        303 ns    2305282
//   is_greater_stdstring_loop/32768              2737 ns       2737 ns     254906
//   is_greater_stdstring_loop/262144            25908 ns      25908 ns      26954
//   is_greater_stdstring_loop/1048576          487813 ns     487820 ns       1305
//   is_greater_cstring_loop/1                       2 ns          2 ns  281642619
//   is_greater_cstring_loop/8                       2 ns          2 ns  281300605
//   is_greater_cstring_loop/64                      2 ns          2 ns  280949124
//   is_greater_cstring_loop/512                     2 ns          2 ns  281791923
//   is_greater_cstring_loop/4096                    2 ns          2 ns  281864136
//   is_greater_cstring_loop/32768                   2 ns          2 ns  280746279
//   is_greater_cstring_loop/262144                  2 ns          2 ns  280401718
//   is_greater_cstring_loop/1048576                 2 ns          2 ns  277589138


bool is_greater_str(const std::string& a, const std::string& b) { return a > b; }
bool is_greater_cstr(const char* a, const char* b) { return std::strcmp(a, b) > 0; }

volatile int val = 0;

static void is_greater_stdstring_loop_same(benchmark::State& state)
{
    std::string str1(state.range(0), 'M');
    std::string str2(state.range(0), 'M');
    const char *cstr1 = str1.c_str();
    const char *cstr2 = str2.c_str();

    while(state.KeepRunning())
        benchmark::DoNotOptimize(val += is_greater_str(cstr1, cstr2));
}

static void is_greater_cstring_loop_same(benchmark::State& state)
{
    std::string str1(state.range(0), 'M');
    std::string str2(state.range(0), 'M');
    const char *cstr1 = str1.c_str();
    const char *cstr2 = str2.c_str();

    while(state.KeepRunning())
        benchmark::DoNotOptimize(val=is_greater_cstr(cstr1, cstr2));
}

static void is_greater_stdstring_loop(benchmark::State& state)
{
    std::string str1(state.range(0), 'M');
    std::string str2(state.range(0), 'N');
    const char *cstr1 = str1.c_str();
    const char *cstr2 = str2.c_str();

    while(state.KeepRunning())
        benchmark::DoNotOptimize(val += is_greater_str(cstr1, cstr2));
}

static void is_greater_cstring_loop(benchmark::State& state)
{
    std::string str1(state.range(0), 'M');
    std::string str2(state.range(0), 'N');
    const char *cstr1 = str1.c_str();
    const char *cstr2 = str2.c_str();

    while(state.KeepRunning())
        benchmark::DoNotOptimize(val=is_greater_cstr(cstr1, cstr2));
}

BENCHMARK(is_greater_stdstring_loop_same)->Range(1, 1<<20);
BENCHMARK(is_greater_cstring_loop_same)->Range(1, 1<<20);
BENCHMARK(is_greater_stdstring_loop)->Range(1, 1<<20);
BENCHMARK(is_greater_cstring_loop)->Range(1, 1<<20);

BENCHMARK_MAIN();
