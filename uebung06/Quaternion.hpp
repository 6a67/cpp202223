/**
 *  @file Quaternion.hpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */


#ifndef __QUATERNION_HPP__
#define __QUATERNION_HPP__

#include "Vector.hpp"
#include "Matrix.hpp"

#include <iostream>
#include <cmath>

namespace asteroids
{

/**
 * @brief   Quaternion representation for OpenGL. Based on:
 *          http://gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
 *
 */
class Quaternion
{
public:
    /**
     * @brief   Constructs a default quaternion object
     */
    Quaternion();

    /**
     * @brief   Destructor
     */
    ~Quaternion();

    /**
     * @brief   Constructs (with fromAxis()) a quaternion with a given Vector and an angle
     * @param vec vector
     * @param angle angle
     */
    Quaternion(const Vector& vec, float angle);

    /**
     * @brief   Constructs a quaternion with three given values and an angle
     * @param x x-value
     * @param y y-value
     * @param z z-value
     * @param w angle
     */
    Quaternion(float x, float y, float z, float w);

    /**
     * @brief   Constructs a quaternion with a given float-pointer and an angle
     * @param vec vector(pointer)
     * @param w angle
     */
    Quaternion(float* vec, float w);

    /**
     * @brief   Copy constructor
     * @param q quaternion to copy
     */
    Quaternion(const Quaternion& q);

    /**
     * @brief   Calculates a quaternion with a given vector and an angle
     * @param axis vector
     * @param angle angle
     */
    void fromAxis(const Vector& axis, float angle);

    /**
     * @brief   Overloaded assignment operator
     */
    Quaternion& operator=(const Quaternion& q);

    /**
     * @brief Overloaded operator for quaternion multiplication
     */
    Quaternion operator*(const Quaternion& other) const;

    /**
     * @brief Overloaded operator for quaternion multiplication and assignment
     */
    Quaternion& operator*=(const Quaternion& other);

    /**
     * @brief Overloaded operator for quaternion multiplication with vector
     */
    Vector operator*(const Vector& other) const;

    /**
     * @brief Return a matrix representation of the quaternion
     */
    Matrix toMatrix() const;

    void print();

private:
    /**
     * @brief   Value of angle, x, y and z
     */
    float w, x, y, z;

    Quaternion getConjugate() const;
};

}  // namespace asteroids

#endif
