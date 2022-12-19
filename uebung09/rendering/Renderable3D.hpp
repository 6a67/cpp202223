/*
 *  Renderable3D.hpp
 *
 *  Created on: Nov. 25 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __RENDERABLE3D_HPP__
#define __RENDERABLE3D_HPP__

#include "Renderable.hpp"
#include "math/Matrix.hpp"
#include "math/Quaternion.hpp"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace asteroids
{
/**
 * @brief A class to represent renderable objects in 3D space.
 * 
 */
class Renderable3D : public Renderable 
{
public:
    enum ACTION{ACCEL, STRAFE, LIFT, YAW, PITCH, ROLL};


    /**
     * @brief Renders the TriangleMesh
     * 
     */
    virtual void render() = 0;

     /**
	 * @brief   Rotates a triangle mesh at the given axis with the given speed
	 * @param axis axis to rotate
	 * @param speed speed of rotation
	 */
	void rotate(ACTION axis, float speed);

	/**
	 * @brief   Moves a triangle mesh at the given axis with the given speed
	 * @param axis axis to move
	 * @param speed speed of movement
	 */
	void move(ACTION axis, float speed);

    void setPosition(const Vector3f& pos);

protected:

    /// Initializes the transformations
    void initTransformations();

    /**
	 * @brief Computes the 4x4 transformation matrix for 
     * this object (needed for OpenGL)
	 */
	void computeMatrix();

    /// X axis of local coordinate system
    Vector3f      m_xAxis;

    /// Y axis of local coordinate system
    Vector3f      m_yAxis;

    /// Z axus of local coordinate system
    Vector3f      m_zAxis;

    /// Transformation matrix
    Matrix      m_transformation;

    /// Current rotation
    Quaternion  m_rotation;

    /// Current position
    Vector3f      m_position;

};

} // asteroids


#endif