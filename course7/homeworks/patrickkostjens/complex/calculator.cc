#include "calculator.hh"

#include <regex>

void Calculator::print_status(std::ostream& stream) const
{
    if (stack.empty()) stream << "empty" << std::endl;
    else stream << stack.top() << std::endl;
}

void Calculator::process_line(const std::string& line)
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

        auto second = stack.top();
        stack.pop();
        auto first = stack.top();
        stack.pop();

        if (line == "+") stack.push(first + second);
        else if (line == "-") stack.push(first - second);
        else if (line == "*") stack.push(first * second);
        else if (line == "/") stack.push(first / second);
        else throw std::runtime_error("Unknown operator");
    }
    else stack.push(parse_complex_input(line));
}

Complex Calculator::parse_complex_input(const std::string& line) const
{
    static const std::regex regex("^(-?[0-9]+.[0-9]+) ?(([+-]) ?[iI]([0-9]+.[0-9]+))?$");

    std::smatch match;
    if (!std::regex_match(line, match, regex)) throw std::runtime_error("Invalid number");

    Complex c(std::stod(match[1].str()));
    if (match[4].matched) c.imaginary = std::stod(match[3].str() + match[4].str());

    return c;
}
