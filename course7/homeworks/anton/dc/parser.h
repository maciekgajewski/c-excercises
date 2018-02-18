#pragma once

class Parser
{
public:
    Parser(std::istream& s) : mStream(s)
    {

    }

    void skip_whitespace()
    {
        if (std::isspace(mStream.peek())) {
            mStream >> std::ws;
            infix_extempt = false;
        }
    }

    bool eof()
    {
        skip_whitespace();
        return mStream.eof() || 'q' == mStream.peek();
    }

    bool number_is_comming()
    {
        return '_' == mStream.peek() || 'i' == mStream.peek() || ('0' <= mStream.peek() && mStream.peek() <= '9');
    }

    char get_command()
    {
        char command = std::cin.get();
        infix_extempt = infix_extempt && ('+' == command || '-' == command) && 'i' == std::cin.peek();
        return command;
    }

    bool extempt_is_applicable()
    {
        return infix_extempt;
    }

    Complex read_number()
    {
        Complex number;
        mStream >> number;
        if (number.is_real())
            infix_extempt = true;
        return number;
    }

private:
    std::istream& mStream;
    bool infix_extempt = false;
};
