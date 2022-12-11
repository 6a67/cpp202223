#include "MatrixProxy.hpp"
#include "OutOfBoundsException.hpp"

namespace asteroids
{

MatrixProxy::MatrixProxy(float* data, int size)
{
    m_row  = data;
    m_size = size;
}

float& MatrixProxy::operator[](int index)
{
    if (index < 0 || index >= m_size)
    {
        throw OutOfBoundsException("Index out of bounds");
    }
    return m_row[index];
}

}  // namespace asteroids