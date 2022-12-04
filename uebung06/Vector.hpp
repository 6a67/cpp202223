/**
 *  @file Vector.hpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __Vector_HPP__
#define __Vector_HPP__

#include <iostream>
#include <cmath>

namespace asteroids
{

/**
 * @brief   Vector representation with three floats for OpenGL
 *
 */
class Vector
{
public:
    /**
     * @brief   Construcs a default Vector object
     */
    Vector();

    /**
     * @brief   Construcs a Vector object with given values
     * @param x x-value
     * @param y y-value
     * @param z z-value
     */
    Vector(float x, float y, float z);

    /**
     * @brief   Copy constructor
     */
    Vector(const Vector& v);

    /**
     * @brief   Normalize a Vector
     */
    void normalize();

    /**
     * @brief Overloaded operator for vector addition
     */
    Vector operator+(const Vector& other) const;

    /**
     * @brief Overloaded operator for vector addition and assignment
     */
    Vector& operator+=(const Vector& other);

    /**
     * @brief Overloaded operator for vector multiplication with a scalar
     */
    Vector operator*(float scalar) const;

    /**
     * @brief Overloaded operator for vector multiplication with a scalar and assignment
     */
    Vector& operator*=(float scalar);

    /**
     * @brief Overloaded operator for vector scale division
     */
    Vector operator/(float scalar) const;

    /**
     * @brief Overloaded operator for vector scale division and assignment
     */
    Vector& operator/=(float scalar);

    /**
     * @brief Overloaded operator for vector addition with a scalar
     */
    Vector operator+(float scalar) const;

    /**
     * @brief Overloaded operator for vector addition with a scalar and assignment
     */
    Vector& operator+=(float scalar);

    /**
     * @brief Overloaded operator for vector subtraction
     */
    Vector operator-(const Vector& other) const;

    /**
     * @brief Overloaded operator for vector subtraction and assignment
     */
    Vector& operator-=(const Vector& other);

    /**
     * @brief Overloaded operator for vector dot product
     */
    float operator*(const Vector& other) const;

    /**
     * @brief Overloaded operator for vector assignment
     */
    Vector& operator=(const Vector& other);

    void print();

    /**
     * @brief   The three values of a vector
     */
    float x, y, z;

    /**
     * @brief   Destructor
     */
    ~Vector();
};

}  // namespace asteroids

#endif
