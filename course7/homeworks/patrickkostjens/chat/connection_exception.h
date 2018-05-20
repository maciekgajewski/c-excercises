#pragma once

#include <string>

class ConnectionException: public std::exception {
public:
    explicit ConnectionException(const std::string& message) : m_message(message){};
    virtual const char* what() const throw() {
        return m_message.c_str();
    }
private:
    std::string m_message;
};