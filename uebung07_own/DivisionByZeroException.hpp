#ifndef DIVISIONBYZEROEXCEPTION_HPP
#define DIVISIONBYZEROEXCEPTION_HPP

#include "BaseException.hpp"

namespace asteroids
{

class DivisionByZeroException : public BaseException
{
public:
    // Constructor that takes an error message
    DivisionByZeroException(const std::string& message)
    : BaseException(message)
    {
    }
};


}  // namespace asteroids


#endif