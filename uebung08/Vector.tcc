
/**
 *  @file Vector.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "Vector.hpp"

namespace asteroids
{

template<typename T, int L>
Vector<T, L>::Vector()
{
    // Default values
    for (int i = 0; i < L; i++)
    {
        m_data[i] = 0;
    }
}


template<typename T, int L>
Vector<T, L>::Vector(T _x, T _y, T _z)
{
    // Set the given values
    m_data[0] = _x;
    m_data[1] = _y;
    if (L == 3)
    {
        m_data[2] = _z;
    }
}

template<typename T, int L>
void Vector<T, L>::normalize()
{
    // Normalize the Vector
    float mag2 = 0;
    for (int i = 0; i < L; i++)
    {
        mag2 += m_data[i] * m_data[i];
    }

    if (fabs(mag2 - 1.0f) > 0.00001)
    {
        float mag = sqrt(mag2);
        for (int i = 0; i < L; i++)
        {
            m_data[i] /= mag;
        }
    }
}

template<typename T, int L>
Vector<T, L> Vector<T, L>::operator+(const Vector& vec) const
{
    // Add value to value
    float tx = x + vec.x;
    float ty = y + vec.y;
    
    if (L == 3)
    {
        float tz = z + vec.z;
        return Vector(tx, ty, tz);
    }
    else
    {
        return Vector(tx, ty);
    }
}

template<typename T, int L>
Vector<T, L> Vector<T, L>::operator-(const Vector& vec) const
{
    // Subtract value from value
    float tx = x - vec.x;
    float ty = y - vec.y;
    
    if (L == 3)
    {
        float tz = z - vec.z;
        return Vector(tx, ty, tz);
    }
    else
    {
        return Vector(tx, ty);
    }

}

template<typename T, int L>
T Vector<T, L>::operator[](const int& index) const
{
    // TODO: Erklärung
    if (index >= L)
    {
        throw std::invalid_argument("Vector index out of range");
    }

    return m[index];
}

template<typename T, int L>
T& Vector<T, L>::operator[](const int& index)
{
    if (index >= L)
    {
        throw std::invalid_argument("Vector index out of range");
    }

    return m[index];
}


template<typename T, int L>
T Vector<T, L>::operator*(const Vector& vec) const
{
    if(L != vec.dimension)
    {
        throw std::invalid_argument("Vector dimension mismatch");
    }

    // Calculate the result
    T result = 0;
    for (int i = 0; i < L; i++)
    {
        result += m_data[i] * vec.m_data[i];
    }
    return result;
}

template<typename T, int L>
Vector<T, L> Vector<T, L>::operator*(T scale) const
{
    // Calculate the result
    float tx = m[0] * scale;
    float ty = m[1] * scale;

    if (L == 3)
    {
        float tz = m[2] * scale;
        return Vector(tx, ty, tz);
    }
    else
    {
        return Vector(tx, ty);
    }
}

template<typename T, int L>
void Vector<T, L>::operator+=(const Vector& v)
{
    // Add value to value
    m[0] += v[0];
    m[1] += v[1];
    if (L == 3)
    {
        m[2] += v[2];
    }
}

}  // namespace asteroids
