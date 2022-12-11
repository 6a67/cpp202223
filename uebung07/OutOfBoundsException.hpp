//
// Created by sascha on 11.12.22.
//

#ifndef CPP18_ASTEROIDS_OUTOFBOUNDSEXCEPTION_HPP
#define CPP18_ASTEROIDS_OUTOFBOUNDSEXCEPTION_HPP

#include "BaseException.hpp"

namespace asteroids
{
class OutOfBoundsException : public BaseException
{
public:
    OutOfBoundsException(const std::string& message) : BaseException(message)
    {
    }
};
} // namespace asteroids

#endif //CPP18_ASTEROIDS_OUTOFBOUNDSEXCEPTION_HPP
