#include <string>
#include <cstring>
#include <benchmark/benchmark.h>
#include <iostream>

bool is_greater_string(const std::string& a, const std::string& b) { return a>b; }
bool is_greater(const char* a, const char* b) { return std::strcmp(a, b) > 0;}

/*const char* create_char(int N, std::string a)
{
    std::string input = a;
    for(int i = 0; i < N; i++) { input += a; }
    //const char* inputchar = input.c_str();
    return input;
}*/

std::string create_char(int N, std::string a)
{
    std::string input = a;
    for(int i = 0; i < N; i++) { input += a; }
    //const char* inputchar = input.c_str();
    return input;
}

static void is_greater_bench(benchmark::State& state)
{
    std::string a = "a";
    std::string z = "z";
    std::string input1 = a;
    std::string input2 = z;
    for(int i = 0; i < state.range(0); i++)
    {
         input1 += a;
         input2 += z;
    }
    const char* inputchar1 = input1.c_str();
    const char* inputchar2 = input2.c_str();

    while(state.KeepRunning())
        benchmark::DoNotOptimize( is_greater(inputchar1, inputchar2 ));
}

static void is_greater_string_bench(benchmark::State& state)
{
    std::string a = "a";
    std::string z = "z";
    std::string input1 = a;
    std::string input2 = z;
    for(int i = 0; i < state.range(0); i++)
    {
         input1 += a;
         input2 += z;
    }
    const char* inputchar1 = input1.c_str();
    const char* inputchar2 = input2.c_str();

    while(state.KeepRunning())
        benchmark::DoNotOptimize( is_greater_string(inputchar1, inputchar2) );
}


BENCHMARK(is_greater_bench)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000);
BENCHMARK(is_greater_string_bench)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000);
BENCHMARK_MAIN();