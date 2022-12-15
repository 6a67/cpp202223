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
 * @brief   Vector representation with three floats for OpenGL.
 *
 * @todo	Replace this float-specific implementation for three coordinates
 * 			with a generic version called 'Vector' that supports 2 to 3 coordinates
 * 			with different types. Here we will use float and int for space
 * 			and screen coordinates respectively.
 */
// generic vector class with dimension and type as template parameters
template<typename T, int L>
class Vector
{
    /*
        The static_assert enforces that the vector can only have
        the sizes 2 or 3 at compile time. If the vector is somewhere
        initialized with a different size, the compiler will throw
        an error message that is somewhat helpful than an error
        that the implementation of the vector with a different size
        is missing. Depending on the use case there could also be
        runtime errors because the implementation of the vector/the
        functions of the vector only make sense for 2 or 3 dimensions.
    */
    static_assert(L >= 2 && L <= 3, "Vector dimension must be 2 or 3");

public:
    /**
     * @brief   Construcs a default Vector3f object
     */
    Vector();

    /**
     * @brief   Construcs a Vector object with given values
     */
    Vector(T x, T y, T z = 0);

    /**
     * @brief   Normalize a Vector
     */
    void normalize();

    /**
     * @brief        Overloaded assignment operator for Vector class
     * @param other  The Vector object to be assigned
     * @return   A reference to the Vector object being assigned
     */
    Vector& operator=(const Vector& other);

    /**
     * @brief   Defines the vector addition
     * @param vec vector
     * @return vector
     */
    Vector operator+(const Vector& vec) const;

    /**
     * @brief   Defines the vector subtraction
     * @param vec vector
     * @return vector
     */
    Vector operator-(const Vector& vec) const;

    /**
     * @brief   Construcs the scalar multiplication
     * @param scale scalar
     * @return vector
     */
    Vector operator*(const T scale) const;

    /**
     * @brief   Defines the vector multiplication
     * @param vec vector
     * @return result (as a float)
     */
    T operator*(const Vector& vec) const;

    /**
     * @brief   Defines the access to a Vector value
     * @param index wanted value
     * @return vectorentry (as a float)
     */
    T operator[](const int& index) const;

    /**
     * @brief   Defines the access to a Vector value
     * @param index wanted value
     * @return vectorentry (as a float)
     */
    T& operator[](const int& index);

    /**
     * @brief   Defines the fast notation of vector addition
     * @param v vector
     */
    void operator+=(const Vector& v);

protected:
    // The values of a vector
    T m[L];
};


typedef Vector<float, 3> Vector3f;
typedef Vector<int, 2>   Vector2i;

}  // namespace asteroids

#include "Vector.tcc"
#endif
