#include "functions.hh"

#include <benchmark/benchmark.h>

#include <vector>
#include <algorithm>



static void to_doubles_becnhmark(benchmark::State& state)
{
    const char* argv[] = { "1", "2.2", "3.3", "4.4", "5.5", "6.6", "7.7", "8.8", "9.9", "110.100" };
    int argc = 10;
    
    while(state.KeepRunning()) {
        std::vector<double> res = paramsToNumbers(argc, argv);
    }
}

BENCHMARK(to_doubles_becnhmark);

BENCHMARK_MAIN();