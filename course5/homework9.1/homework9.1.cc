#include <string>
#include <cstring>
#include <benchmark/benchmark.h>


const int NUM_COMPARISON_TYPES = 2;
const int SLOW_EQUAL = 0;
const int FAST_GREATER = 1;

bool is_greater(const std::string& a, const std::string& b) { return a > b; }
bool is_greater(const char* a, const char* b) { return std::strcmp(a, b) > 0; }

template <typename T>
static void BM_ComparisonEqual(benchmark::State & state)
{
	int size = state.range(0);
	char ** c = new char *[2];
	for (int i = 0; i < 2; i++)
	{
		c[i] = new char[size];
		for (int j = 0; j < size; j++)
		{
			c[i][j] = '0' + (j % 10);
		}
	}
	switch(state.range(1)) {
	case SLOW_EQUAL:
		break;
	case FAST_GREATER:
		c[0][size / 10]++;
		break;
	}
	bool result;
	while (state.KeepRunning())
	{
		result = is_greater(T(c[0]), T(c[1]));
	}
	result = !result;
	delete[] c[1];
	delete[] c[0];
	delete[] c;
}

static void Arguments(benchmark::internal::Benchmark* b) {
	for (int sizeStep = 0; sizeStep < 11; sizeStep++) {
		for (int comparisonType = 0; comparisonType < NUM_COMPARISON_TYPES; comparisonType++)
		{
			b->Args({1 << sizeStep << sizeStep, comparisonType});
		}
	}
}
BENCHMARK_TEMPLATE(BM_ComparisonEqual, std::string)->Apply(Arguments);
BENCHMARK_TEMPLATE(BM_ComparisonEqual, char *)->Apply(Arguments);

BENCHMARK_MAIN();
