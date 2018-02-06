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
	~Complex() = default;
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

	double real = 0.0;
	double imaginary = 0.0;
};


bool operator==(Complex lhs, Complex rhs)
{
	return lhs.real == rhs.real && lhs.imaginary == rhs.imaginary;
}

std::ostream& operator<<(std::ostream& stream, const Complex& complex)
{
	stream << complex.real << "i" << complex.imaginary;
	return stream;
}

class Calculator
{
public:
	Calculator(const std::string& l) : line(l) {}

	void execute()
	{
		std::size_t i = 0;
		while (i < line.length())
		{
			switch (line[i])
			{
			case '+':
				add();
				i++;
				break;
			case '-':
				subtract();
				i++;
				break;
			case '*':
				multiply();
				i++;
				break;
			case '/':
				divide();
				i++;
				break;
			default:
				i = parseAndPushComplex(i);
			}

			while (i < line.length() && line[i] == ' ')
				i++;
		}

		if (stack.empty())
			std::cout << "empty" << std::endl;
		else
			std::cout << stack.top() << std::endl;
	}

private:
	std::size_t parseAndPushComplex(std::size_t startIndex)
	{
		static const std::regex regex("^([0-9]+.[0-9]+)(?:i([0-9]+.[0-9]+))?");

		std::smatch match;
		std::string::const_iterator begin = line.begin() + startIndex;
		std::string::const_iterator end = line.end();
		bool found = std::regex_search(begin, end, match, regex);

		if (!found || match.size() > 3)
		{
			std::stringstream s;
			s << "Could not parse complex number at pos " << startIndex << " in line: \"" << line << "\"";
			throw std::runtime_error(s.str());
		}

		Complex c(std::stod(match[1].str()));
		if (match[3].matched)
			c.imaginary = std::stod(match[2].str());

		stack.push(c);
		return startIndex + match.length();
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
	std::string line;
	std::stack<Complex> stack;
};

int main(/*int argc, char** argv*/)
{
	Calculator ca("12.34i12.34 12.34i12.34 +");
	ca.execute();

	ca = Calculator("12.34 12.34i12.34 +");
	ca.execute();

	ca = Calculator("12.34i12.34 12.34i12.34 -");
	ca.execute();

	ca = Calculator("12.34i12.34 12.34i12.34 *");
	ca.execute();

	ca = Calculator("2.0 1.0 * 2.0 4.0 * + 5.0 -");
	ca.execute();

	/*for (std::string line; std::getline(std::cin, line); ) {
		Calculator c(line);
		c.execute();
	}*/
}
