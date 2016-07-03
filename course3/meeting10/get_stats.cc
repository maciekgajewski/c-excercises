#include "get_stats.hh"

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <numeric>

#include <boost/range/numeric.hpp>
#include <boost/range/algorithm.hpp>

// returns average, median
std::tuple<double, double> get_stats(int count ,char** args)
{
	if (count <= 0)
	{
		throw std::invalid_argument("Empty range passed to get_stats");
	}
	
	std::vector<double> doubles;
	doubles.resize(count);
	std::transform(args, args+count, doubles.begin(), [](char* input){return std::stod(input);});
	assert(doubles.size() == count);
	
	boost::sort(doubles);
	double median = doubles[count/2];
	
	double sum = boost::accumulate(doubles, 0.0);
	
	return std::make_tuple(sum/count, median);
}