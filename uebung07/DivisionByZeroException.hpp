//
// Created by sascha on 11.12.22.
//

#ifndef CPP18_ASTEROIDS_DIVISIONBYZEROEXCEPTION_HPP
#define CPP18_ASTEROIDS_DIVISIONBYZEROEXCEPTION_HPP

#include "BaseException.hpp"

namespace asteroids
{
class DivisionByZeroException : public BaseException
{
public:
    DivisionByZeroException(const std::string& message) : BaseException(message)
    {
    }
};
} // namespace asteroids

#endif //CPP18_ASTEROIDS_DIVISIONBYZEROEXCEPTION_HPP
