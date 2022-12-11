//
// Created by sascha on 11.12.22.
//
#ifndef ASTEROIDS_BASEEXCEPTION_HPP
#define ASTEROIDS_BASEEXCEPTION_HPP

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
    const char* what() const throw() override { return m_message.c_str(); }

private:
    // The error message
    std::string m_message;
};

}  // namespace asteroids
#endif  // ASTEROIDS_BASEEXCEPTION_HPP
