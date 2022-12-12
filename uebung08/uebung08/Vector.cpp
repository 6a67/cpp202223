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

namespace asteroids {
    
Vector3f::Vector3f()
{
	// Default values
	x = y = z = 0.0;
}


Vector3f::Vector3f(float _x, float _y, float _z)
{
	// Set the given values
	x = _x;
	y = _y;
	z = _z; 
}

void Vector3f::normalize()
{
	// Normalize the Vector3f
	float mag2 = x * x + y * y + z * z;
	if (fabs(mag2 - 1.0f) > 0.00001)
	{
		float mag = sqrt(mag2);
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

Vector3f Vector3f::operator+(const Vector3f& vec) const
{
	// Add value to value
	float tx = x + vec.x;
	float ty = y + vec.y;
	float tz = z + vec.z;
	return Vector3f(tx, ty, tz);
}

Vector3f Vector3f::operator-(const Vector3f& vec) const
{
	// Subtract value from value
	float tx = x - vec.x;
	float ty = y - vec.y;
	float tz = z - vec.z;
	return Vector3f(tx, ty, tz);
}


float Vector3f::operator[](const int &index) const
{
	
	// Get the wanted value
	if(index == 0)
	{
		return x;
	}

	if(index == 1)
	{
		return y;
	}

	if(index == 2)
	{
		return z;
	}

	return 0;
}
    
    
float& Vector3f::operator[](const int &index)
{

    if(index == 0)
    {
        return x;
    }
        
    if(index == 1)
    {
        return y;
    }
        
    if(index == 2)
    {
        return z;
    }
    
    // Return a defualt reference -> later throw exception!!
    return x;
}


    

float Vector3f::operator*(const Vector3f& vec) const
{
  // Calculate the result
  return (x * vec.x + y * vec.y + z * vec.z); 
}

Vector3f Vector3f::operator*(float scale) const
{
	// Calculate the result
	float tx = x * scale;
	float ty = y * scale;
	float tz = z * scale;
	return Vector3f(tx, ty, tz);
}

void Vector3f::operator+=(const Vector3f& v)
{
	// Add value to value
	x += v.x;
	y += v.y;
	z += v.z;
}
    
} // namespace asteroids
