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

Vector::Vector()
{
    // Default values
    x = y = z = 0.0;
}


Vector::Vector(float _x, float _y, float _z)
{
    // Set the given values
    x = _x;
    y = _y;
    z = _z;
}

void Vector::normalize()
{
    // Normalize the vector
    float mag2 = x * x + y * y + z * z;
    if (fabs(mag2 - 1.0f) > 0.00001)
    {
        float mag = sqrt(mag2);
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

Vector::Vector(const Vector& v)
: x(v.x)
, y(v.y)
, z(v.z)
{
}


Vector Vector::operator+(const Vector& other) const
{
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector& Vector::operator+=(const Vector& other)
{
    *this = *this + other;
    return *this;
}

Vector Vector::operator*(float scalar) const
{
    return Vector(x * scalar, y * scalar, z * scalar);
}

Vector& Vector::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector Vector::operator/(float scalar) const
{
    return *this * (1.0f / scalar);
}

Vector& Vector::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}

Vector Vector::operator+(float scalar) const
{
    return Vector(x + scalar, y + scalar, z + scalar);
}

Vector& Vector::operator+=(float scalar)
{
    *this = *this + scalar;
    return *this;
}

Vector Vector::operator-(const Vector& other) const
{
    return Vector(x - other.x, y - other.y, z - other.z);
}

Vector& Vector::operator-=(const Vector& other)
{
    *this = *this - other;
    return *this;
}

float Vector::operator*(const Vector& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

void Vector::print()
{
    std::cout << "Vector(" << x << ", " << y << ", " << z << ")" << std::endl;
}

Vector::~Vector()
{
}


}  // namespace asteroids
