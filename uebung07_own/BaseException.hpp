#ifndef BASEEXCEPTION_HPP
#define BASEEXCEPTION_HPP

#include <string>

namespace asteroids
{

class BaseException : public std::exception
{
public:
    // Constructor that takes an error message
    BaseException(const std::string& message)
    : m_message(message)
    {
    }

    // Returns the error message
    virtual const char* what() const throw() { return m_message.c_str(); }

private:
    // The error message
    std::string m_message;
};

}  // namespace asteroids
#endif