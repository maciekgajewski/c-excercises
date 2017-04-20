#include <benchmark/benchmark.h>

#include <vector>
#include <stdexcept>
#include <iostream>

std::int64_t total;

std::vector<int> get_seq_vector(int size);
std::vector<int> get_random_vector(int size);

enum Order { SEQ, RAND };

template <Order order>
static void access_benchmark(benchmark::State& state)
{
	std::int64_t size = state.range(0);
	int use_rand = state.range(1);

	std::vector<int> v;
	if (order == SEQ)
		v = get_seq_vector(size);
	else
		v = get_random_vector(size);
	
// 	for(int i : v)
// 		std::cerr << i << " ";
// 	std::cerr << std::endl;
	
	total = 0;
	while(state.KeepRunning())
	{
		std::int64_t idx = 0;
		std::int64_t tot = 0;
		for(std::int64_t i = 0; i < size; i++)
		{
			int val = v[idx];
			tot += val;
			idx = val;
		}
		total = tot;
	}
	
	// verify
	std::int64_t expected_total = (size * (size-1)) /2;
	if (total != expected_total)
	{
		std::cerr << "r0=" << state.range(0) << std::endl;
		//std::cerr << "inc=" << inc << std::endl;
		std::cerr << "tot = " << total << ", exp=" << expected_total << std::endl;
		throw std::logic_error("Not all elements visited!");
	}
	
}

BENCHMARK_TEMPLATE(access_benchmark, SEQ)->RangeMultiplier(2)->Range(1<<4, 1<<25);
BENCHMARK_TEMPLATE(access_benchmark, RAND)->RangeMultiplier(2)->Range(1<<4, 1<<25);

BENCHMARK_MAIN();