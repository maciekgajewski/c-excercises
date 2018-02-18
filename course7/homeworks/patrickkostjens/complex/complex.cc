#include <cmath>
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <string>
#include <regex>

struct Complex
{
	double real = 0.0;
	double imaginary = 0.0;

	Complex() = default;
	Complex(double r) : real(r) {}
	Complex(double r, double i) : real(r), imaginary(i) {}

	Complex(const Complex& other) : real(other.real), imaginary(other.imaginary) {}

	Complex& operator= (const Complex& other)
	{
		real = other.real;
		imaginary = other.imaginary;
		return *this;
	}

	Complex operator+ (const Complex& rhs) const
	{
		return { real + rhs.real, imaginary + rhs.imaginary };
	}

	Complex operator- (const Complex& rhs) const
	{
		return { real - rhs.real, imaginary - rhs.imaginary };
	}

	Complex operator* (const Complex& rhs) const
	{
		return {
			(real * rhs.real) - (imaginary * rhs.imaginary),
			(real * rhs.imaginary) + (imaginary * rhs.real)
		  };
	}

	Complex operator/ (const Complex& rhs) const
	{
		return {
			((real * rhs.real) + (imaginary * rhs.imaginary)) / ((rhs.real * rhs.real) + (rhs.imaginary * rhs.imaginary)),
			((imaginary * rhs.real) - (real * rhs.imaginary)) / ((rhs.real * rhs.real) + (rhs.imaginary * rhs.imaginary))
		  };
	}

	bool operator== (const Complex& rhs) const
	{
		return real == rhs.real && imaginary == rhs.imaginary;
	}
};

std::ostream& operator<< (std::ostream& stream, const Complex& complex)
{
	stream << complex.real << (complex.imaginary >= 0 ? "+" : "-") << "i" << std::abs(complex.imaginary);
	return stream;
}

class Calculator
{
public:
	void print_status(std::ostream& stream) const
	{
		if (stack.empty()) stream << "empty" << std::endl;
		else stream << stack.top() << std::endl;
	}
	void process_line(const std::string& line)
	{
		if (line.length() == 1)
		{
			if (line == "q") exit(EXIT_SUCCESS);
			if (line == "c")
			{
				while(!stack.empty()) stack.pop();
				return;
			}

			if (stack.size() < 2) throw std::runtime_error("Not enough elements on stack");

			auto first = stack.top();
			stack.pop();
			auto second = stack.top();
			stack.pop();

			if (line == "+") stack.push(first + second);
			else if (line == "-") stack.push(first - second);
			else if (line == "*") stack.push(first * second);
			else if (line == "/") stack.push(first / second);
			else throw std::runtime_error("Unknown operator");
		}
		else stack.push(parse_complex_input(line));
	}

private:
	std::stack<Complex> stack;

	Complex parse_complex_input(const std::string& line) const
	{
		static const std::regex regex("^(-?[0-9]+.[0-9]+) ?(([+-]) ?[iI]([0-9]+.[0-9]+))?$");

		std::smatch match;
		if (!std::regex_match(line, match, regex)) throw std::runtime_error("Invalid number");

		Complex c(std::stod(match[1].str()));
		if (match[4].matched) c.imaginary = std::stod(match[3].str() + match[4].str());

		return c;
	}
};

int main(int argc, char** argv)
{
	Calculator c;
	std::string line;
	while(true)
	{
		std::getline(std::cin, line);
		try
		{
			c.process_line(line);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		c.print_status(std::cout);
	}
}
