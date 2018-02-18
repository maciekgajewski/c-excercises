#pragma once

class Parser
{
public:
    Parser(std::istream& s) : mStream(s)
    {

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

    char read_command()
    {
        return static_cast<char>(std::cin.get());
    }

    Complex read_number()
    {
        Complex number;
        mStream >> number;
        return number;
    }

    void skip_whitespace()
    {
        mStream >> std::ws;
    }
private:
    std::istream& mStream;
};
