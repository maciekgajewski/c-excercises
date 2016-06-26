#include "list.h"

#include <list>
#include <forward_list>
#include <algorithm>
#include <benchmark/benchmark.h>


template<template<typename...> class ListType>
void ListBenchmark(benchmark::State& state)
{
	ListType<int> l;
	for (int i=0; i < state.range_x(); ++i)
		l.push_front(i);
}

//BENCHMARK_TEMPLATE(ListBenchmark, Karun::List)->Range(1<<0, 1<<10);
//BENCHMARK_TEMPLATE(ListBenchmark, std::list)->Range(1<<0, 1<<10);
//BENCHMARK_TEMPLATE(ListBenchmark, std::forward_list)->Range(1<<0, 1<<10);

//BENCHMARK_MAIN();

// Placeholder for BENCHMARK_MAIN
int main() {}
