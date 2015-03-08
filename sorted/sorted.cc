/* Please, write a program program that accepts any number of
 * command-line parameters, and then prints them to stdout sorted.
 * Example session:
 * ./my_prog The quick brown fox jumps over the lazy dog
 * The brown dog fox jumps lazy over quick the
 *
 * Please, use the following tools:
 * std::vector for storing the parameters
 * std::sort to sort the container
 * std::copy and std::ostream_iterator to print the output
 *
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>


int main(int argc, char** argv) {

	if (argc <= 1) return 0;

	std::vector<std::string> parameters (argv + 1, argv + argc);

	std::sort(parameters.begin(), parameters.end());

	std::ostream_iterator<std::string > out_it (std::cout, " ");

	// No logic to avoid a delimiter after the last element
	std::copy(parameters.begin(), parameters.end(), out_it);

	std::cout << std::endl;

	return 0;
}
