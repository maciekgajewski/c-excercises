#include <iostream>
#include <string>

using namespace std::literals;

int max(int a, int b) { return a > b ? a : b; }
double max(double a, double b) { return a > b ? a : b; }
std::string max(std::string a, std::string b) { return a > b ? a : b; }

int main(int argc, char** argv)
{
	std::cout << max(7, 99) << std::endl;
	std::cout << max(5.5, 42.7) << std::endl;
	std::cout << max("Ariel"s, "Maciek"s) << std::endl;
}

