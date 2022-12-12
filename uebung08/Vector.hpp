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
class Vector3f {

public:

	/**
	 * @brief   Construcs a default Vector3f object
	 */
	Vector3f();

	/**
	 * @brief   Construcs a Vector object with given values
	 * @param x x-value
	 * @param y y-value
	 * @param z z-value
	 */
	Vector3f(float x, float y, float z);

	/**
	 * @brief   Normalize a Vector
	 */
	void normalize();
  
	/**
	 * @brief   Defines the vector addition
	 * @param vec vector
	 * @return vector
	 */
	Vector3f operator+ (const Vector3f& vec) const;

	/**
	 * @brief   Defines the vector subtraction
	 * @param vec vector
	 * @return vector
	 */
	Vector3f operator- (const Vector3f& vec) const;

	/**
	 * @brief   Construcs the scalar multiplication
	 * @param scale scalar
	 * @return vector
	 */
	Vector3f operator* (const float scale) const;

	/**
	 * @brief   Defines the vector multiplication
	 * @param vec vector
	 * @return result (as a float)
	 */
	float  operator* (const Vector3f& vec) const;

	/**
	 * @brief   Defines the access to a Vector value
	 * @param index wanted value
	 * @return vectorentry (as a float)
	 */
	float operator[] (const int& index) const;
    
    /**
     * @brief   Defines the access to a Vector value
     * @param index wanted value
     * @return vectorentry (as a float)
     */
    float& operator[] (const int& index);

	/**
	 * @brief   Defines the fast notation of vector addition
	 * @param v vector
	 */
	void operator+= (const Vector3f& v);

	/**
	 * @brief   The three values of a vector
	 */
	float x, y, z;
};
    
/***
 * TODO: 	This is just a plain simple replacement for 
 * 			the generic version you are going to implement 
 * 			in this exercise that just gives us the needed index operator 
 * 		    based coordinate access. Replace it with a suitable
 * 			typedef of your generic implementation.
 **/
struct Vector2i
{
	Vector2i(int x, int y)
	{
		m[0] = x;
		m[1] = y;
	}

	int& operator[](const int& index)
	{
		if(index >= 0 && index <= 2)
		{
			return m[index];
		}
		throw std::invalid_argument("");
	}

	int operator[](const int& index) const
	{
		if(index >= 0 && index <= 2)
		{
			return m[index];
		}
		throw std::invalid_argument("");
	}

	int m[2];	 	
};

} // namespace asteroids

#endif
