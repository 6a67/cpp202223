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

constexpr double TOLERANCE = 0.00000000000000000000000000000000000000000000001;

/**
 * @brief   Vector representation with three floats for OpenGL
 *
 */
template<typename T, int L = 3>
class Vector {

public:

	/**
	 * @brief   Construcs a default Vector object
	 */
	Vector(T x = 0, T y = 0, T z = 0);

	/**
	 * @brief   Normalize a Vector
	 */
	void normalize();
  
	/**
	 * @brief   Defines the vector addition
	 * @param vec vector
	 * @return vector
	 */
	Vector<T, L> operator+ (const Vector<T, L>& vec) const;

	/**
	 * @brief   Defines the vector subtraction
	 * @param vec vector
	 * @return vector
	 */
	Vector<T, L> operator- (const Vector<T, L>& vec) const;

	/**
	 * @brief   Construcs the scalar multiplication
	 * @param scale scalar
	 * @return vector
	 */
	Vector<T, L> operator* (const T& scale) const;

	/**
	 * @brief   Defines the vector multiplication
	 * @param vec vector
	 * @return result (as a float)
	 */
	T  operator* (const Vector<T, L>& vec) const;

	/**
	 * @brief   Defines the access to a Vector value
	 * @param index wanted value
	 * @return vectorentry (as a float)
	 */
	T operator[] (const int& index) const;
    
    /**
     * @brief   Defines the access to a Vector value
     * @param index wanted value
     * @return vectorentry (as a float)
     */
    T& operator[] (const int& index);

	/**
	 * @brief   Defines the fast notation of vector addition
	 * @param v vector
	 */
	void operator+= (const Vector<T, L>& v);

	// Distance to other vertex
    T  dist(const Vector<T, L> &vec);


protected:
	 /**
	 * @brief   The internal values of the vector
	 */
	T m[L];
};

/**
 * @brief Cross product for three dimensional vectors
 * 
 * @param a First vector
 * @param b Second vector
 * 
 * @return Result vector
 */
template<typename T>
Vector<T, 3> cross(Vector<T, 3>& a, Vector<T, 3>& b);

typedef Vector<float, 3> Vector3f;
typedef Vector<int, 2> Vector2i;
    
} // namespace asteroids

#include "Vector.tcc"

#endif
