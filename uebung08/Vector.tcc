
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
        m[i] = 0;
    }
}


template<typename T, int L>
Vector<T, L>::Vector(T _x, T _y, T _z)
{
    // Set the given values
    m[0] = _x;
    m[1] = _y;
    if (L == 3)
    {
        m[2] = _z;
    }
}

template<typename T, int L>
void Vector<T, L>::normalize()
{
    // Normalize the Vector
    float mag2 = 0;
    for (int i = 0; i < L; i++)
    {
        mag2 += m[i] * m[i];
    }

    if (fabs(mag2 - 1.0f) > 0.00001)
    {
        float mag = sqrt(mag2);
        for (int i = 0; i < L; i++)
        {
            m[i] /= mag;
        }
    }
}

template<typename T, int L>
Vector<T, L> Vector<T, L>::operator+(const Vector& vec) const
{
    // Add value to value
    float tx = m[0] + vec[0];
    float ty = m[1] + vec[1];

    if (L == 3)
    {
        float tz = m[2] + vec[2];
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
    float tx = m[0] - vec.x;
    float ty = m[1] - vec.y;

    if (L == 3)
    {
        float tz = m[2] - vec.z;
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
    /*
        A static_assert is a compile time check and therefore
        can not be used with the given index as it is not known
        at compile time. There is also the option to use an
        assert. But an assert is more like a debug check to
        assure that the given index is valid. If the index is
        invalid the program will crash. An exception is something
        that can be handled without crashing the program and
        therefore is more suitable for production.
    */
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
    if (L != vec.dimension)
    {
        throw std::invalid_argument("Vector dimension mismatch");
    }

    // Calculate the result
    T result = 0;
    for (int i = 0; i < L; i++)
    {
        result += m[i] * vec[i];
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

template<typename T, int L>
Vector<T, L>& Vector<T, L>::operator=(const Vector& other)
{
    if (this != &other)
    {
        m[0] = other[0];
        m[1] = other[1];
    }

    if (L == 3)
    {
        m[2] = other[2];
    }
    return *this;
}

}  // namespace asteroids
