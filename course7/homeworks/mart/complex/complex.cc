#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <regex>

struct Complex
{
	Complex() = default;
	Complex(double r) : real(r) {}
	Complex(double r, double i) : real(r) , imaginary(i) {}
	Complex(const Complex& src) : real(src.real) , imaginary(src.imaginary) {}

	Complex& operator=(const Complex& src)
	{
		real = src.real;
		imaginary = src.imaginary;
		return *this;
	}

	Complex operator+(const Complex& rhs) const
	{
		return { real + rhs.real, imaginary + rhs.imaginary };
	}

	Complex operator-(const Complex& rhs) const
	{
		return { real - rhs.real, imaginary - rhs.imaginary };
	}

	Complex operator*(const Complex& rhs) const
	{
		return {
			(real * rhs.real) - (imaginary * rhs.imaginary),
			(real * rhs.imaginary) + (imaginary * rhs.real)
		  };
	}

	Complex operator/(const Complex& rhs) const
	{
		return {
			((real * rhs.real) + (imaginary * rhs.imaginary)) / ((rhs.real * rhs.real) + (rhs.imaginary * rhs.imaginary)),
			((imaginary * rhs.real) - (real * rhs.imaginary)) / ((rhs.real * rhs.real) + (rhs.imaginary * rhs.imaginary))
		  };
	}

	bool operator==(const Complex& rhs)
	{
		return real == rhs.real && imaginary == rhs.imaginary;
	}

	double real = 0.0;
	double imaginary = 0.0;
};

std::ostream& operator<<(std::ostream& stream, const Complex& complex)
{
	stream << complex.real << "+i" << complex.imaginary;
	return stream;
}

class Calculator
{
public:
	void run()
	{
		for (std::string line; std::getline(std::cin, line); )
		{
			try
			{
				if (line == "+")
					add();
				else if (line == "-")
					subtract();
				else if (line == "*")
					multiply();
				else if (line == "/")
					divide();
				else
					parseAndPushComplex(line);
			}
			catch(const std::exception& e)
			{
				std::cerr << "Error executing line: " << e.what() << std::endl;
			}
			if (stack.empty())
				std::cout << "empty" << std::endl;
			else
				std::cout << stack.top() << std::endl;
		}
	}

private:
	void parseAndPushComplex(const std::string& line)
	{
		static const std::regex regex("^([0-9]+.[0-9]+)(?:\\+i([0-9]+.[0-9]+))?$");

		std::smatch match;
		bool found = std::regex_match(line, match, regex);

		if (!found || match.size() != 3)
			throw std::runtime_error("Cannot parse complex number");

		Complex c(std::stod(match[1].str()));
		if (match[2].matched)
			c.imaginary = std::stod(match[2].str());

		stack.push(c);
	}

	std::pair<Complex, Complex> popPair()
	{
		if (stack.size() < 2)
			throw std::runtime_error("Stack does not contain 2 items");
		std::pair<Complex, Complex> pair;
		pair.first = stack.top();
		stack.pop();
		pair.second = stack.top();
		stack.pop();
		return pair;
	}

	void add()
	{
		auto pair = popPair();
		stack.push(pair.second + pair.first);
	}

	void subtract()
	{
		auto pair = popPair();
		stack.push(pair.second - pair.first);
	}

	void multiply()
	{
		auto pair = popPair();
		stack.push(pair.second * pair.first);
	}

	void divide()
	{
		auto pair = popPair();
		stack.push(pair.second / pair.first);
	}

private:
	std::stack<Complex> stack;
};

int main(/*int argc, char** argv*/)
{
	Calculator c;
	c.run();
}
