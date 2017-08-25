/*

ARS/20170405

Homework1:

Use google benchmark to compare the performance of these two functions:

bool is_greater(const std::string& a, const std::string& b) { return a > b; }
bool is_greater(const char* a, const char* b) { return std::strcmp(a, b) > 0; }


in a context when they are both called with const char* parameters. Test different length of the input string, from 1 char to 1MB (or even longer, if you so fancy or if results are interesting).

Be mindful on what you’re measuring!

Output:
anil@anil-VirtualBox:~/cc/week9/debug$ ./homework09 
Run on (1 X 3698.93 MHz CPU )
2017-04-05 23:15:45
***WARNING*** Library was built as DEBUG. Timings may be affected.
-------------------------------------------------------------------------
Benchmark                                  Time           CPU Iterations
-------------------------------------------------------------------------
is_greater_stdstring_loop/1               12 ns         12 ns   54107312
is_greater_stdstring_loop/8               12 ns         12 ns   56405826
is_greater_stdstring_loop/64              12 ns         12 ns   97076944
is_greater_stdstring_loop/512             19 ns         19 ns   36336319
is_greater_stdstring_loop/4096            12 ns         12 ns   56822159
is_greater_stdstring_loop/32768           12 ns         12 ns   56628651
is_greater_stdstring_loop/262144          12 ns         12 ns   56824993
is_greater_stdstring_loop/1048576         12 ns         12 ns   56135011
is_greater_cstring_loop/1                  3 ns          3 ns  251906120
is_greater_cstring_loop/8                  3 ns          3 ns  253899014
is_greater_cstring_loop/64                 3 ns          3 ns  252124783
is_greater_cstring_loop/512                3 ns          3 ns  250599494
is_greater_cstring_loop/4096               3 ns          3 ns  250478086
is_greater_cstring_loop/32768              3 ns          3 ns  252863104
is_greater_cstring_loop/262144             3 ns          3 ns  251554146
is_greater_cstring_loop/1048576            3 ns          3 ns  251538885


Homework2 to be continued next week. Sorry, short of time this week.
*/

#include <benchmark/benchmark.h>
#include <string>
#include <cstring>
#include <iostream>



bool is_greater_str(const std::string& a, const std::string& b) { return a > b; }
bool is_greater_cstr(const char* a, const char* b) { return std::strcmp(a, b) > 0; }

static void is_greater_stdstring_loop(benchmark::State& state)
{
	bool val;
	const char* str1 = new char[state.range(0)];
	const char* str2 = new char[state.range(0)];
	
	while(state.KeepRunning())
		benchmark::DoNotOptimize(val=is_greater_str(str1, str2));
	
	delete str1;
	delete str2;
	
}

static void is_greater_cstring_loop(benchmark::State& state)
{
	bool val;
	const char* str1 = new char[state.range(0)];
	const char* str2 = new char[state.range(0)];

	while(state.KeepRunning())
		benchmark::DoNotOptimize(val=is_greater_cstr(str1, str2));

	delete str1;
	delete str2;
}

BENCHMARK(is_greater_stdstring_loop)->Range(1, 1<<20);
BENCHMARK(is_greater_cstring_loop)->Range(1, 1<<20);

BENCHMARK_MAIN();
