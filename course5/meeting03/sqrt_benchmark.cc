#include <benchmark/benchmark.h>

#include <cmath>


float q_sqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = *reinterpret_cast<long*>(&y);          // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = *reinterpret_cast<float*>(&i);
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration

	return 1.0f/y;
}

float x;

static void sqrt_bench(benchmark::State& state)
{
	while(state.KeepRunning())
	{
		for(float i = 0.0; i < 1.0; i += 0.01)
			benchmark::DoNotOptimize(x += std::sqrt(i));
	}
}

static void q_sqrt_bench(benchmark::State& state)
{
	while(state.KeepRunning())
		for(float i = 0.0; i < 1.0; i += 0.01)
			benchmark::DoNotOptimize(x+=q_sqrt(i));
}

static void null_loop(benchmark::State& state)
{
	while(state.KeepRunning())
		for(float i = 0.0; i < 1.0; i += 0.01)
			benchmark::DoNotOptimize(x+=i);
}


BENCHMARK(sqrt_bench);
BENCHMARK(q_sqrt_bench);
BENCHMARK(null_loop);

BENCHMARK_MAIN();
