#include <benchmark/benchmark.h>

#include <vector>
#include <list>

#include <algorithm>
#include <random>

template<typename ContainerT>
static void Fill(ContainerT& container, std::size_t size)
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 1000);

	for(std::size_t i = 0; i < size; i++)
	container.push_back(dist(rd));
}

template<typename ContainerT>
static void AccumulateBenchmark(benchmark::State& state)
{
	auto size = state.range(0);
	state.counters["size"] = size*sizeof(int);
	ContainerT container;
	Fill(container, size);

	for(auto _ : state)
		benchmark::DoNotOptimize(std::accumulate(container.begin(), container.end(), 0));
}

BENCHMARK_TEMPLATE(AccumulateBenchmark, std::vector<int>)->RangeMultiplier(4)->Range(1<<10, 1<<24);
BENCHMARK_TEMPLATE(AccumulateBenchmark, std::list<int>)->RangeMultiplier(4)->Range(1<<10, 1<<24);
BENCHMARK_MAIN();