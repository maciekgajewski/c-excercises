#include <random>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <chrono>
#include <ios>
#include <iomanip>

using namespace std::literals::chrono_literals;
using floatMillis = std::chrono::duration<double, std::milli>;

struct RNG
{
	std::default_random_engine randEngine;
	std::uniform_real_distribution<double> realDist{0, 1000};
	double operator() () { return realDist(randEngine); }
};

template <typename F>
void PrintTime(F func, const char* message)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;

	std::vector<std::chrono::nanoseconds> measurements(100);

	// warmup
	for ( int i = 0; i < 10; i++ )
		func();

	//benchmark
	for ( int i = 0; i < 100; i++ ) {
		start = std::chrono::system_clock::now();
		func();
		end = std::chrono::system_clock::now();
		measurements[i] = end-start;
	}

	std::nth_element(measurements.begin(), measurements.begin()+50, measurements.end());

	std::streamsize prec = std::cout.precision();
	std::cout << message << " Median: ";
	std::cout << std::fixed << std::setprecision(3) << std::chrono::duration_cast<floatMillis>(measurements[50])/1ms;

	std::nth_element(measurements.begin(), measurements.begin(), measurements.end());

	std::cout << ", Min: " << std::chrono::duration_cast<floatMillis>(measurements[0])/1ms;
	std::cout << std::setprecision(prec) << " ms" << std::endl;
}


int main()
{
	int N = 1000000;
	RNG randomGen;

	std::vector<double> v;
	std::list<double> l;
	std::deque<double> d;

	PrintTime([&]() {
			v = std::vector<double>(N);
			std::generate_n(v.begin(), N, randomGen);
		}, "Populate vector: ");
	PrintTime([&]() {
			l = std::list<double>(N,0);
			std::generate_n(l.begin(), N, randomGen);
		}, "Populate list  : ");
	PrintTime([&]() {
			d = std::deque<double>(N,0);
			std::generate_n(d.begin(), N, randomGen);
		}, "Populate deque : ");

	PrintTime([&]() {std::accumulate(v.begin(), v.end(), 0);}, "Sum vector: ");
	PrintTime([&]() {std::accumulate(l.begin(), l.end(), 0);}, "Sum list  : ");
	PrintTime([&]() {std::accumulate(d.begin(), d.end(), 0);}, "Sum deque : ");

	PrintTime([&]() {std::sort(v.begin(), v.end());}, "Sort vector: ");
	PrintTime([&]() {l.sort();}, "Sort list  : ");
	PrintTime([&]() {std::sort(d.begin(), d.end());}, "Sort deque : ");

	PrintTime([&]() {std::nth_element(v.begin(), v.begin() + 100, v.end());}, "Nth element vector: ");
	PrintTime([&]() {std::nth_element(d.begin(), d.begin() + 100, d.end());}, "Nth element deque : ");

	return 0;
}
