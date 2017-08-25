#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <benchmark/benchmark.h>

#include "linked_list.h"

template <typename T>
static void push_back(T & container, int element)
{
	container.push_back(element);
}

static void push_back(jds::LinkedList<int> & list, int element)
{
	std::vector<int> temp;
	while (list.size())
	{
		temp.push_back(list.front());
		list.pop_front();
	}
	list.push_front(element);
	while (!temp.empty())
	{
		list.push_front(temp.back());
		temp.pop_back();
	}
}


template <typename T>
static void BM_Container(benchmark::State & state)
{
	T container;
	for (int i = 0; i < 100; i++)
		push_back(container, i);
	while (state.KeepRunning())
	{
		benchmark::DoNotOptimize(std::accumulate(container.begin(), container.end(), 0));
	}
}


BENCHMARK_TEMPLATE(BM_Container, std::vector<int>);
BENCHMARK_TEMPLATE(BM_Container, std::list<int>);
BENCHMARK_TEMPLATE(BM_Container, std::deque<int>);
BENCHMARK_TEMPLATE(BM_Container, jds::LinkedList<int>);

// Results
// jfdsmit@paranor:~/werk/optiver/c-excercises/course5/homework11.1/build$ make && ./homework11.1
// [100%] Built target homework11.1
// Run on (2 X 2400 MHz CPU s)
// 2017-04-18 22:20:06
// --------------------------------------------------------------------------
// Benchmark                                   Time           CPU Iterations
// --------------------------------------------------------------------------
// BM_Container<std::vector<int>>           1884 ns       1883 ns     368819
// BM_Container<std::list<int>>             1083 ns       1082 ns     642249
// BM_Container<std::deque<int>>            1945 ns       1945 ns     359572
// BM_Container<jds::LinkedList<int>>       2863 ns       2863 ns     244860
//

BENCHMARK_MAIN();
