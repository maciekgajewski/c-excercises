#include "list.h"

#include <list>
#include <forward_list>
#include <deque>
#include <algorithm>
#include <benchmark/benchmark.h>


template<template<typename...> class ListType>
void ListBenchmark(benchmark::State& state)
{
	while (state.KeepRunning())
	{
		ListType<int> l;
		for (int i=0; i < state.range_x(); ++i)
			l.push_front(i);
	}
}

BENCHMARK_TEMPLATE(ListBenchmark, std::deque)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(ListBenchmark, std::list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(ListBenchmark, std::forward_list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(ListBenchmark, Karun::List)->Range(1<<0, 1<<20);

BENCHMARK_MAIN();