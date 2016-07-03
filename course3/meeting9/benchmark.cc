#include <benchmark/benchmark.h>

#include <vector>
#include <list>
#include <random>
#include <algorithm>

volatile int global_i = 0;

template<typename Container>
static void accumulate_becnhmark(benchmark::State& state)
{
    std::minstd_rand engine;
    std::uniform_int_distribution<int> dist(-10, +10);
    
    int size = state.range_x();
    
    Container container;
    for(int i = 0; i < size; i++)
        container.push_back(dist(engine));

    while(state.KeepRunning()) {
        global_i = std::accumulate(container.begin(), container.end(), 0);
    }
}

BENCHMARK_TEMPLATE(accumulate_becnhmark, std::vector<int>)->Range(1<<1, 1<<20);
BENCHMARK_TEMPLATE(accumulate_becnhmark, std::list<int>)->Range(1<<1, 1<<20);

BENCHMARK_MAIN();