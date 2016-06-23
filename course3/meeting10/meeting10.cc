#include "get_stats.hh"

#include <iostream>

int main(int argc, char** argv)
{
	double avg, median;
	
	std::tie(avg, median) = get_stats(argc-1, argv+1);
	
	std::cout << "Avg: " << avg << std::endl;
	std::cout << "Median: " << median << std::endl;
}
