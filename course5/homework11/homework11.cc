#include <benchmark/benchmark.h>

#include <vector>
#include <deque>
#include <list>
#include <forward_list>

#include <chrono>
#include <numeric>
#include <random>
#include <algorithm>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::int64_t sum;

// homework 11
//    Run on (4 X 3301 MHz CPU s)
//    --------------------------------------------------------------------------------------------------
//    Benchmark                                                           Time           CPU Iterations
//    --------------------------------------------------------------------------------------------------
//    container_iterate<std::vector<std::int64_t>>/1                      1 ns          1 ns  499876809
//    container_iterate<std::vector<std::int64_t>>/8                      4 ns          4 ns  176725594
//    container_iterate<std::vector<std::int64_t>>/64                    32 ns         32 ns   22084288
//    container_iterate<std::vector<std::int64_t>>/512                  200 ns        200 ns    3513744
//    container_iterate<std::vector<std::int64_t>>/4096                1568 ns       1566 ns     451966
//    container_iterate<std::vector<std::int64_t>>/32768              13600 ns      13600 ns      51372
//    container_iterate<std::vector<std::int64_t>>/262144            118154 ns     118154 ns       6141
//    container_iterate<std::vector<std::int64_t>>/1048576           746047 ns     746050 ns       1034
//    container_iterate<std::deque<std::int64_t>>/1                       2 ns          2 ns  395733753
//    container_iterate<std::deque<std::int64_t>>/8                       4 ns          4 ns  187200415
//    container_iterate<std::deque<std::int64_t>>/64                     37 ns         37 ns   18807574
//    container_iterate<std::deque<std::int64_t>>/512                   298 ns        298 ns    2353087
//    container_iterate<std::deque<std::int64_t>>/4096                 2449 ns       2449 ns     282176
//    container_iterate<std::deque<std::int64_t>>/32768               20895 ns      20896 ns      34292
//    container_iterate<std::deque<std::int64_t>>/262144             182355 ns     182354 ns       3990
//    container_iterate<std::deque<std::int64_t>>/1048576            875519 ns     875528 ns        811
//    container_iterate<std::list<std::int64_t>>/1                        2 ns          2 ns  461601051
//    container_iterate<std::list<std::int64_t>>/8                        4 ns          4 ns  181253537
//    container_iterate<std::list<std::int64_t>>/64                      82 ns         82 ns    8451783
//    container_iterate<std::list<std::int64_t>>/512                    615 ns        615 ns    1115601
//    container_iterate<std::list<std::int64_t>>/4096                  8041 ns       8041 ns     105005
//    container_iterate<std::list<std::int64_t>>/32768                74888 ns      74883 ns      12206
//    container_iterate<std::list<std::int64_t>>/262144              952901 ns     952912 ns        921
//    container_iterate<std::list<std::int64_t>>/1048576            4319511 ns    4319472 ns        210
//    container_iterate<std::forward_list<std::int64_t>>/1                1 ns          1 ns  496980817
//    container_iterate<std::forward_list<std::int64_t>>/8                4 ns          4 ns  182891051
//    container_iterate<std::forward_list<std::int64_t>>/64              82 ns         82 ns    8388364
//    container_iterate<std::forward_list<std::int64_t>>/512            614 ns        614 ns    1094662
//    container_iterate<std::forward_list<std::int64_t>>/4096          8159 ns       8160 ns      82686
//    container_iterate<std::forward_list<std::int64_t>>/32768        76913 ns      76914 ns       8639
//    container_iterate<std::forward_list<std::int64_t>>/262144      994663 ns     994656 ns        725
//    container_iterate<std::forward_list<std::int64_t>>/1048576    4194906 ns    4194941 ns        169

template<class Container>
void push_element(Container &c, const typename Container::value_type &value)
{
    c.push_back(value);
}

template<>
void push_element<std::forward_list<std::int64_t>>(std::forward_list<std::int64_t> &c, const std::int64_t &value)
{
    c.push_front(value);
}

template <class Container>
static void container_iterate(benchmark::State& state)
{
    Container c;
    for (std::int64_t i=0; i<state.range(0); ++i)
        push_element(c, i);

    while(state.KeepRunning())
        benchmark::DoNotOptimize(sum=std::accumulate(std::begin(c), std::end(c), 0));
}

BENCHMARK_TEMPLATE(container_iterate, std::vector<std::int64_t>)->Range(1, 1<<20);
BENCHMARK_TEMPLATE(container_iterate, std::deque<std::int64_t>)->Range(1, 1<<20);
BENCHMARK_TEMPLATE(container_iterate, std::list<std::int64_t>)->Range(1, 1<<20);
BENCHMARK_TEMPLATE(container_iterate, std::forward_list<std::int64_t>)->Range(1, 1<<20);

// extra homework
//    Run on (4 X 3301 MHz CPU s)
//    ------------------------------------------------------------------------------------------------------------------
//    Benchmark                                                                           Time           CPU Iterations
//    ------------------------------------------------------------------------------------------------------------------
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/4                 2 ns          2 ns  284824202
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/16                6 ns          6 ns  108097799
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/64               98 ns         98 ns    7066029
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/256             368 ns        368 ns    1907591
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/1024           1466 ns       1465 ns     472506
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/4096           6019 ns       5993 ns     113864
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/16384         24079 ns      24062 ns      29363
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/65536         97437 ns      97438 ns       7176
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/262144       405554 ns     405560 ns       1696
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/1048576     1733046 ns    1733064 ns        396
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/4194304     6815916 ns    6815987 ns        104
//    container_iterate_ordered<std::vector<std::int64_t>, linear_read>/16777216   27327719 ns   27328124 ns         25
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/4                 1 ns          1 ns  605364317
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/16                3 ns          3 ns  245728914
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/64               65 ns         65 ns   10402075
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/256             184 ns        184 ns    3797266
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/1024            454 ns        454 ns    1531389
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/4096           5140 ns       5140 ns     128880
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/16384         19641 ns      19641 ns      36058
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/65536        275419 ns     275422 ns       2545
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/262144       665141 ns     665148 ns        977
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/1048576    59257278 ns   59258197 ns         12
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/4194304   331046738 ns  331015530 ns          2
//    container_iterate_ordered<std::vector<std::int64_t>, random_read>/16777216  637214053 ns  637223792 ns          1
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/4                  3 ns          3 ns  205591442
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/16                14 ns         14 ns   49619123
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/64               116 ns        116 ns    5953433
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/256              830 ns        830 ns     852626
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/1024            3676 ns       3676 ns     189874
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/4096           15381 ns      15382 ns      45404
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/16384          62110 ns      62111 ns      11327
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/65536         248474 ns     248477 ns       2840
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/262144       1021970 ns    1021982 ns        690
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/1048576      4219404 ns    4219452 ns        167
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/4194304     16760140 ns   16757844 ns         42
//    container_iterate_ordered<std::deque<std::int64_t>, linear_read>/16777216    67287268 ns   67287883 ns         10
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/4                  2 ns          2 ns  310438844
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/16                 6 ns          6 ns  118006811
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/64                81 ns         81 ns    8594129
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/256              367 ns        367 ns    1890390
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/1024            1091 ns       1091 ns     638900
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/4096           14110 ns      14110 ns      49528
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/16384          34955 ns      34956 ns      19839
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/65536         367182 ns     367186 ns       1881
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/262144        956106 ns     956115 ns        760
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/1048576     78667157 ns   78667654 ns          9
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/4194304    435734658 ns  435739838 ns          2
//    container_iterate_ordered<std::deque<std::int64_t>, random_read>/16777216   938941599 ns  938953250 ns          1

// Plotting the results:
// $ ./homework11 --benchmark_repetitions=10 --benchmark_report_aggregates_only=true --benchmark_format=csv --benchmark_out=read_benchmark.csv
// $ grep "vector.*linear_read.*mean" read_benchmark.csv | sed 's/"[^/]*\/\([0-9]\+\)_mean"/\1/' > vector_linear.csv
// $ grep "vector.*random_read.*mean" read_benchmark.csv | sed 's/"[^/]*\/\([0-9]\+\)_mean"/\1/' > vector_random.csv
// $ grep "deque.*linear_read.*mean" read_benchmark.csv | sed 's/"[^/]*\/\([0-9]\+\)_mean"/\1/' > deque_linear.csv
// $ grep "deque.*random_read.*mean" read_benchmark.csv | sed 's/"[^/]*\/\([0-9]\+\)_mean"/\1/' > deque_random.csv
// $ gnuplot
// gnuplot> set datafile separator ","
// gnuplot> plot 'vector_linear.csv' using 1:3 title "vector linear" with lines, 'vector_random.csv' using 1:3 title "vector random" with lines, 'deque_linear.csv' using 1:3 title "deque linear" with lines, 'deque_random.csv' using 1:3 title "deque random" with lines

enum ReadMode { linear_read, random_read};

template <class Container, ReadMode order>
static void container_iterate_ordered(benchmark::State& state)
{
    Container c;
    for (std::int64_t i=1; i<=state.range(0); ++i)
        c.push_back(i);
    if (order == random_read)
    {
        std::shuffle(std::begin(c), std::end(c), std::default_random_engine(seed));
    }

    while(state.KeepRunning())
    {
        size_t pos = 0;
        while (pos<c.size())
            pos = c[pos];
    }
}

static void CustomListSize(benchmark::internal::Benchmark* b)
{
    for (int i=4; i < 2<<25; i <<= 1)
        b->Args({i});
}

BENCHMARK_TEMPLATE(container_iterate_ordered, std::vector<std::int64_t>, linear_read)->Apply(CustomListSize);
BENCHMARK_TEMPLATE(container_iterate_ordered, std::vector<std::int64_t>, random_read)->Apply(CustomListSize);
BENCHMARK_TEMPLATE(container_iterate_ordered, std::deque<std::int64_t>, linear_read)->Apply(CustomListSize);
BENCHMARK_TEMPLATE(container_iterate_ordered, std::deque<std::int64_t>, random_read)->Apply(CustomListSize);

BENCHMARK_MAIN();
