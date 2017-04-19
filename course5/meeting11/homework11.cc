/*

ARS/20170419

Homework11:

Conclusions: 
* vector random iteration or sequential iteration do not matter that much
* list iterations seems faster than vector which is faster than deque

-----------------------------------------------------------------------------------
Benchmark                                            Time           CPU Iterations
-----------------------------------------------------------------------------------
test_vector_iter/1                                  37 ns         36 ns   19477603
test_vector_iter/8                                 161 ns        153 ns    4694465
test_vector_iter/64                                988 ns        951 ns     694386
test_vector_iter/512                              7300 ns       7179 ns      96476
test_vector_iter/4096                            57179 ns      56966 ns      11984
test_vector_iter/32768                          470608 ns     466093 ns       1513
test_vector_iter/262144                        3951464 ns    3869737 ns        177
test_vector_iter/1048576                      15853472 ns   15384362 ns         44
test_vector_random_iter/1                           35 ns         35 ns   19842417
test_vector_random_iter/8                          150 ns        146 ns    4738064
test_vector_random_iter/64                         935 ns        921 ns     745273
test_vector_random_iter/512                       7227 ns       7198 ns      94597
test_vector_random_iter/4096                     58059 ns      57517 ns      11459
test_vector_random_iter/32768                   458108 ns     457470 ns       1526
test_vector_random_iter/262144                 3700070 ns    3687319 ns        190
test_vector_random_iter/1048576               15044845 ns   14975820 ns         47
container_test<std::list<double>>/1                 29 ns         29 ns   24375178
container_test<std::list<double>>/8                 80 ns         80 ns    8489830
container_test<std::list<double>>/64               492 ns        488 ns    1373139
container_test<std::list<double>>/512             3711 ns       3709 ns     187277
container_test<std::list<double>>/4096           29897 ns      29775 ns      23235
container_test<std::list<double>>/32768         247032 ns     246805 ns       2865
container_test<std::list<double>>/262144       2130263 ns    2101877 ns        314
container_test<std::list<double>>/1048576      8432452 ns    8204384 ns         83
container_test<std::vector<double>>/1               31 ns         31 ns   23041500
container_test<std::vector<double>>/8               89 ns         89 ns    7432025
container_test<std::vector<double>>/64             582 ns        579 ns    1153674
container_test<std::vector<double>>/512           4440 ns       4428 ns     157642
container_test<std::vector<double>>/4096         35143 ns      35056 ns      19877
container_test<std::vector<double>>/32768       278389 ns     278366 ns       2475
container_test<std::vector<double>>/262144     2240467 ns    2238286 ns        308
container_test<std::vector<double>>/1048576    9151687 ns    9140093 ns         78
container_test<std::deque<double>>/1                39 ns         39 ns   18043925
container_test<std::deque<double>>/8               117 ns        117 ns    5834165
container_test<std::deque<double>>/64              771 ns        767 ns     892666
container_test<std::deque<double>>/512            5991 ns       5978 ns     111456
container_test<std::deque<double>>/4096          47551 ns      47338 ns      14824
container_test<std::deque<double>>/32768        397526 ns     390936 ns       1823
container_test<std::deque<double>>/262144      3171094 ns    3099803 ns        217
container_test<std::deque<double>>/1048576    12565289 ns   12345663 ns         55
*/

#include <benchmark/benchmark.h>
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

template <typename T>
void container_test(benchmark::State& state)
{
	//T container(state.range(0), 3.14);
	T container;
	double result;

	for (int i=0; i < state.range(0);i++)
		container.push_back(i*3.14);

	while(state.KeepRunning())
		benchmark::DoNotOptimize(result = std::accumulate(container.begin(), container.end(), 0.0));

}
	
void test_vector_random_iter(benchmark::State& state)
{
	std::vector<double> myvector(state.range(0), 3.14);
	double sum = 0.; 

	// from stackoverflow http://stackoverflow.com/questions/18993998/iterating-over-the-array-in-random-order
	std::random_shuffle ( myvector.begin(), myvector.end() );  // in place no extra array

	while (state.KeepRunning())
		for (std::vector<double>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
   			benchmark::DoNotOptimize(sum+= *it);
}


void test_vector_iter(benchmark::State& state)
{
	std::vector<double> myvector(state.range(0), 3.14);
	double sum = 0.;

	while (state.KeepRunning())
		for (std::vector<double>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
   			benchmark::DoNotOptimize(sum+= *it);
}

BENCHMARK(test_vector_iter)->Range(1, 1<<20);
BENCHMARK(test_vector_random_iter)->Range(1, 1<<20);

BENCHMARK_TEMPLATE(container_test, std::list<double>)->Range(1, 1<<20);
BENCHMARK_TEMPLATE(container_test, std::vector<double>)->Range(1, 1<<20);
BENCHMARK_TEMPLATE(container_test, std::deque<double>)->Range(1, 1<<20);
BENCHMARK_MAIN();
