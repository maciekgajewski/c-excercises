#include <iostream>
#include <string>
#include <stack>

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
				break;
			case '-':
				subtract();
				break;
			case '*':
				multiply();
				break;
			case '/':
				divide();
				break;
			default:
				i = parseComplex(i);
			}
			i++;
		}
	}

private:
	std::size_t parseComplex(std::size_t& startIndex)
	{
		return startIndex;
	}

	std::pair<Complex, Complex> popPair()
	{
		if (stack.size() <= 2)
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
		stack.push(pair.first + pair.second);
	}

	void subtract()
	{
		auto pair = popPair();
		stack.push(pair.first - pair.second);
	}

	void multiply()
	{
		auto pair = popPair();
		stack.push(pair.first * pair.second);
	}

	void divide()
	{
		auto pair = popPair();
		stack.push(pair.first / pair.second);
	}

private:
	std::string line;
	std::stack<Complex> stack;
};

int main(/*int argc, char** argv*/)
{
	Complex d = {1.1, 4.4};
	Complex b(7.7);
	std::cout << b << std::endl;

	for (std::string line; std::getline(std::cin, line); ) {
		Calculator c(line);
		c.execute();
	}
}
