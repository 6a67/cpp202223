/**
 *  @file Quaternion.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "Quaternion.hpp"

namespace asteroids
{

Quaternion::Quaternion()
{
	// Default Quaternion
	x = 1.0;
	y = 0.0;
	z = 0.0;
	w = 0.0; 
}

Quaternion::~Quaternion()
{
	// Do nothing
}

Quaternion::Quaternion(const Vector& vec, float angle)
{
	// Calculate the quaternion
	fromAxis(vec, angle);
}

Quaternion::Quaternion(float _x, float _y, float _z, float _angle)
{
	// Set the values
	x = _x;
	y = _y;
	z = _z;
	w = _angle;
}

Quaternion::Quaternion(float* vec, float _w)
{
	// Set the values
	x = vec[0];
	y = vec[1];
	z = vec[2];
	w = _w;
}

void Quaternion::fromAxis(const Vector& axis, float angle)
{
	float sinAngle;
	angle *= 0.5f;

	// Create a copy of the given vector and normalize the new vector
	Vector vn(axis.x, axis.y, axis.z);
	vn.normalize();
 
	// Calculate the sinus of the given angle
	sinAngle = sin(angle);
 
	// Get the quaternion
	x = (vn.x * sinAngle);
	y = (vn.y * sinAngle);
	z = (vn.z * sinAngle);
	w = cos(angle);
}

    
}
