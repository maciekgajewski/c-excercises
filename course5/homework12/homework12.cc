#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "line_sorting.h"

using namespace jds;

namespace po = boost::program_options;

static po::variables_map parse_args(int argc, char ** argv)
{
	try {
		po::options_description description{"Options"};
		description.add_options()
			("help,h", "Show this help and exit")
			("separator,s", po::value<std::string>()->default_value("\t"), "Field separator")
			("column,c", po::value<size_t>()->default_value(1), "Column number to sort on")
			("reverse,r", po::bool_switch()->default_value(false), "Sort in reverse order")
			("numeric,n", po::bool_switch()->default_value(false), "Sort numerically")
			("input,i", po::value<std::string>()->default_value("-"), "File to read from ('-' for stdin)")
			("output,o", po::value<std::string>()->default_value(""), "File to write to (blank for stdout");
		po::variables_map result;
		po::store(po::parse_command_line(argc, argv, description), result);
		if (result.count("help"))
		{
			std::cout << description << std::endl;
			std::exit(0);
		}
		return result;
	}
	catch (po::error const & error)
	{
		std::cerr << error.what() << std::endl;
		std::exit(1);
	}
}

int main(int argc, char **argv)
{
	po::variables_map args = parse_args(argc, argv);
	
	std::string inputPath = args["input"].as<std::string>();
	std::fstream inputFile;
	std::istream * input = &std::cin;
	if (inputPath != "-")
	{
		inputFile.open(inputPath, std::ios_base::in);
		if (!inputFile.is_open())
		{
			std::cerr << "Could not open input file " << inputPath << std::endl;
			return 1;
		}
		input = &inputFile;
	}
	std::string separators = args["separator"].as<std::string>();
	size_t column = args["column"].as<size_t>();
	bool reverse = args["reverse"].as<bool>();
	bool numeric = args["numeric"].as<bool>();
	std::string outputPath = args["output"].as<std::string>();
	std::fstream outputFile;
	std::ostream * output = &std::cout;
	if (outputPath != "")
	{
		outputFile.open(outputPath, std::ios_base::out);
		if (!outputFile.is_open())
		{
			std::cerr << "Could not open output file " << outputPath << std::endl;
			return 1;
		}
		output = &outputFile;
	}

	auto lines = ReadLines(*input);
	std::sort(lines.begin(), lines.end(), [&](std::string const & left, std::string const & right)
		  {
			auto leftValue = FindColValue(left, separators.c_str(), column);
			auto rightValue = FindColValue(right, separators.c_str(), column);
			if (numeric)
				return reverse != (ToNumeric(leftValue) < ToNumeric(rightValue));
			else
				return reverse != (leftValue < rightValue);
		  });
	for (std::string line: lines)
	{
		*output << line << std::endl;
	}
	return 0;
}
