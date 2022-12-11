#ifndef OUTOFBOUNDSEXCEPTION_HPP
#define OUTOFBOUNDSEXCEPTION_HPP

#include "BaseException.hpp"

namespace asteroids
{

class OutOfBoundsException : public BaseException
{
public:
    // Constructor that takes an error message
    OutOfBoundsException(const std::string& message)
    : BaseException(message)
    {
    }
};


}  // namespace asteroids


#endif