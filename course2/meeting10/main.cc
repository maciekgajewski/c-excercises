#include <random>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <chrono>
#include <functional>

struct RNG
{
	std::default_random_engine randEngine;
	std::uniform_real_distribution<double> realDist{0, 1000};
	double operator() () { return realDist(randEngine); }
};

void PrintTime(std::function<void()> func, const char* message)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;

	start = std::chrono::system_clock::now();
	func();
	end = std::chrono::system_clock::now();

	std::cout << message << (end-start).count() << std::endl;
}


int main()
{
	int N = 1000000;
	RNG randomGen;

	std::vector<double> v(N);
	std::list<double> l(N,0);
	std::deque<double> d(N,0);

	PrintTime([&]() {std::generate_n(v.begin(), N, randomGen);}, "Populate vector: ");
	PrintTime([&]() {std::generate_n(l.begin(), N, randomGen);}, "Populate list  : ");
	PrintTime([&]() {std::generate_n(d.begin(), N, randomGen);}, "Populate deque : ");

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
