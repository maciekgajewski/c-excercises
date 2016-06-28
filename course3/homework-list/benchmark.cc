#include "list.h"

#include <algorithm>
#include <deque>
#include <list>
#include <forward_list>
#include <memory>
#include <benchmark/benchmark.h>


template<template<typename...> class ListType>
void BM_PushFront(benchmark::State& state)
{
	ListType<int> l;
	
	while (state.KeepRunning())
	{
		for (int i=0; i < state.range_x(); ++i)
			l.push_front(i);
	}
}

template<template<typename...> class ListType>
void BM_Copy(benchmark::State& state)
{
	ListType<int> l, l2;
	for (int i=0; i < state.range_x(); ++i)
		l.push_front(i);
	
	while (state.KeepRunning())
	{
		std::copy(l.begin(), l.end(), std::front_inserter(l2));
	}
}

template<template<typename...> class ListType>
void BM_Move(benchmark::State& state)
{
	ListType<std::unique_ptr<int>> l, l2;
	for (int i=0; i < state.range_x(); ++i)
		l.push_front(std::make_unique<int>(i));
	
	while (state.KeepRunning())
	{
		std::move(l.begin(), l.end(), std::front_inserter(l2));
	}
}

template<template<typename...> class ListType>
void BM_Transform(benchmark::State& state)
{
	ListType<int> l;
	for (int i=0; i < state.range_x(); ++i)
		l.push_front(i);
	
	while (state.KeepRunning())
	{
		std::transform(l.begin(), l.end(), l.begin(), [](int n){ return n * n; });
	}
}


BENCHMARK_TEMPLATE(BM_PushFront, std::deque)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_PushFront, std::list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_PushFront, std::forward_list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_PushFront, Karun::List)->Range(1<<0, 1<<20);

BENCHMARK_TEMPLATE(BM_Copy, std::deque)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_Copy, std::list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_Copy, std::forward_list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_Copy, Karun::List)->Range(1<<0, 1<<20);

BENCHMARK_TEMPLATE(BM_Move, std::deque)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_Move, std::list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_Move, std::forward_list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_Move, Karun::List)->Range(1<<0, 1<<20);

BENCHMARK_TEMPLATE(BM_Transform, std::deque)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_Transform, std::list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_Transform, std::forward_list)->Range(1<<0, 1<<20);
BENCHMARK_TEMPLATE(BM_Transform, Karun::List)->Range(1<<0, 1<<20);

BENCHMARK_MAIN();