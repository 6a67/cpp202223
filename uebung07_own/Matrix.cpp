/*
 * Matrix.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "Matrix.hpp"
#include "OutOfBoundsException.hpp"
#include "DivisionByZeroException.hpp"

namespace asteroids
{

Matrix::Matrix()
{
    for (int i = 0; i < 16; i++)
    {
        m[i] = 0;
    }
    m[0] = m[5] = m[10] = m[15] = 1;
}


/*
    https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/index.htm
    https://www.andre-gaschler.com/rotationconverter/
*/
Matrix::Matrix(Vector axis, float angle)
{
    // Copy vector and normalize it
    Vector v = axis;
    v.normalize();


    for (int i = 0; i < 16; i++)
    {
        m[i] = 0;
    }

    m[0] = m[5] = m[10] = m[15] = 1;

    float c = cos(angle);
    float s = sin(angle);
    float t = 1 - c;

    m[0]  = c + v.x * v.x * t;
    m[5]  = c + v.y * v.y * t;
    m[10] = c + v.z * v.z * t;

    float tmp1 = v.x * v.y * t;
    float tmp2 = v.z * s;

    m[4] = tmp1 + tmp2;
    m[1] = tmp1 - tmp2;

    tmp1 = v.x * v.z * t;
    tmp2 = v.y * s;

    m[8] = tmp1 - tmp2;
    m[2] = tmp1 + tmp2;

    tmp1 = v.y * v.z * t;

    tmp2 = v.x * s;

    m[9] = tmp1 + tmp2;
    m[6] = tmp1 - tmp2;
}

Matrix::Matrix(const Matrix& other)
{
    for (int i = 0; i < 16; i++)
    {
        m[i] = other.m[i];
    }
}

Matrix Matrix::operator+(const Matrix& other) const
{
    Matrix result;
    for (int i = 0; i < 16; i++)
    {
        result.m[i] = m[i] + other.m[i];
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    *this = *this + other;
    return *this;
}


Matrix Matrix::operator*(const Matrix& rhs) const
{
    Matrix result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.m[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++)
            {
                result.m[i * 4 + j] += m[i * 4 + k] * rhs.m[k * 4 + j];
            }
        }
    }
    return result;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    *this = *this * other;
    return *this;
}

Matrix Matrix::operator*(float scalar) const
{
    Matrix result;
    for (int i = 0; i < 16; i++)
    {
        result.m[i] = m[i] * scalar;
    }
    return result;
}

Matrix& Matrix::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}


Vector Matrix::operator*(const Vector& v) const
{
    Vector result;
    result.x = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12];
    result.y = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13];
    result.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14];
    return result;
}

Vector& Matrix::operator*=(Vector& rhs) const
{
    rhs = *this * rhs;
    return rhs;
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        for (int i = 0; i < 16; i++)
        {
            m[i] = other.m[i];
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix& rhs) const
{
    Matrix result;
    for (int i = 0; i < 16; i++)
    {
        result.m[i] = -rhs.m[i];
    }
    return result;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    *this = *this - other;
    return *this;
}


void Matrix::print()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << m[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::operator/(float rhs) const
{
    if (rhs == 0)
    {
        throw DivisionByZeroException("Division by zero in Matrix::operator/");
    }
    return *this * (1.0f / rhs);
}

Matrix& Matrix::operator/=(float rhs)
{
    if (rhs == 0)
    {
        throw DivisionByZeroException("Division by zero in Matrix::operator/=");
    }

    *this = *this / rhs;
    return *this;
}

Matrix& Matrix::operator=(float rhs)
{
    for (int i = 0; i < 16; i++)
    {
        m[i] = rhs;
    }
    return *this;
}


MatrixProxy Matrix::operator[](int index)
{
    if (index < 0 || index > 3)
    {
        throw OutOfBoundsException("Matrix index out of bounds");
    }
    return MatrixProxy(&m[index * 4], 4);
}

void Matrix::transpose()
{
    float tmp;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            tmp          = m[i * 4 + j];
            m[i * 4 + j] = m[j * 4 + i];
            m[j * 4 + i] = tmp;
        }
    }
}


Matrix::~Matrix()
{
}


}  // namespace asteroids
