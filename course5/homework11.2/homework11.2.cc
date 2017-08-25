#include <benchmark/benchmark.h>
#include <vector>
#include <iostream>

static void BM_VectorSequential(benchmark::State & state)
{
	std::vector<int> v(10000000, 42);
	while (state.KeepRunning())
	{
		int result = 0;
		for (size_t i = 0; i < v.size(); i++)
		{
			size_t index;
			benchmark::DoNotOptimize(index = i % 2 ? i : i - 0);
			result += v[index];
		}
	}
}

static void BM_VectorNonSequential(benchmark::State & state)
{
	std::vector<int> v(10000000, 42);
	size_t size = v.size();
	while (state.KeepRunning())
	{
		int result = 0;
		for (size_t i = 0; i < v.size(); i++)
		{
			size_t index;
			benchmark::DoNotOptimize(index = i % 2 ? i : size - i);
			result += v[index];
		}
	}
}


BENCHMARK(BM_VectorSequential);
BENCHMARK(BM_VectorNonSequential);

// Results:
//
// jfdsmit@paranor:~/werk/optiver/c-excercises/course5/homework11.2/build$ make && ./homework11.2
// Scanning dependencies of target homework11.2
// [100%] Building CXX object CMakeFiles/homework11.2.dir/homework11.2.cc.o
// Linking CXX executable homework11.2
// [100%] Built target homework11.2
// Run on (2 X 2400 MHz CPU s)
// 2017-04-19 21:55:18
// --------------------------------------------------------------
// Benchmark                       Time           CPU Iterations
// --------------------------------------------------------------
// BM_VectorSequential      81337172 ns   81337061 ns          9
// BM_VectorNonSequential   98626144 ns   98625775 ns          7
//
// Sequential is indeed slightly faster but not orders of magnitude

BENCHMARK_MAIN();
