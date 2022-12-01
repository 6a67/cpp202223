/*
 *  Model.cpp
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "Model.hpp"
#include "PLYIO.hpp"

#include <iostream>

/* OpenGL / glew Headers */
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

namespace asteroids
{

Model::Model()
{
    // Init member variables
	m_numFaces      = 0;
	m_numVertices   = 0;
	m_vertexBuffer  = 0;
	m_indexBuffer   = 0;

	// Setup rotation and position
	m_xAxis 		= Vector(1.0, 0.0, 0.0);
	m_yAxis 		= Vector(0.0, 1.0, 0.0);
	m_zAxis 		= Vector(0.0, 0.0, 1.0);
	m_position		= Vector(0.0, 0.0, 0.0);

    // Init initial position
    initTransformations();
}

Model::Model(const Model& other)
{
    m_numFaces = other.m_numFaces;
    m_numVertices = other.m_numVertices;
    m_vertexBuffer = new float[3 * m_numVertices];
    m_indexBuffer = new int[3 * m_numFaces];

    m_xAxis = other.m_xAxis;
    m_yAxis = other.m_yAxis;
    m_zAxis = other.m_zAxis;
    m_position = other.m_position;
    m_rotation = other.m_rotation;
    m_transformation = other.m_transformation;
}

Model::Model(int* faces, float* vertices, int a, int b) 
{
	// Save mesh information and buffers
	m_numFaces      = a;
	m_numVertices   = b;
	m_vertexBuffer  = vertices;
	m_indexBuffer   = faces;

	// Init initial position
    initTransformations();
}

Model::Model(const std::string& filename)
{
    LoadPLY(
        filename, 
        m_vertexBuffer, m_indexBuffer, 
        m_numVertices, m_numFaces);

    // Init initial position
    initTransformations();
}

void Model::initTransformations()
 {
    // Setup rotation and position
	m_xAxis 		= Vector(1.0, 0.0, 0.0);
	m_yAxis 		= Vector(0.0, 1.0, 0.0);
	m_zAxis 		= Vector(0.0, 0.0, 1.0);
	m_position		= Vector(0.0, 0.0, 0.0);
	m_rotation.fromAxis(Vector(0.0, 0.0, 1.0), 0.0f);

 }

void Model::rotate(ACTION axis, float s)
{
	// TODO: Implement the rotation of the model based on the 
	// value of axis. Generate a suitable Quaternion that 
	// represents a rotation by 's' radius around the relevant
	// axis. Then use this to rotate the other to base
	// vectors.
	// Remember: Yaw is around y-axis, roll is around x-axis
	// and pitch is around local y-axis
	// CF: http://ros-robotics.blogspot.com/2015/04/getting-roll-pitch-and-yaw-from.html

    switch(axis) {
        case ACTION::ROLL:
            m_rotation = Quaternion(m_rotation * m_zAxis, s) * m_rotation;
            break;
        case ACTION::PITCH:
            m_rotation = Quaternion(m_rotation * m_yAxis, s) * m_rotation;
            break;
        case ACTION::YAW:
            m_rotation = Quaternion(m_rotation * m_xAxis, s) * m_rotation;
            break;
        default:
            break;
    }
}

void Model::move(ACTION axis, float speed)
{
	// TODO:
	// Implement the movement of the model. First, determine the
	// direction in which the movement has to be done using the
	// state of axis. Update the current position of the model
	// by moving 'speed' units in the direction of the relvant 
	// base vector
	// Remember: Accelaration happens in direction of the current 
	// x-Axis, strafing is done in y-direction and lifting 
	// is done in z-direction
	// cf: http://ros-robotics.blogspot.com/2015/04/getting-roll-pitch-and-yaw-from.html

    Vector tmpX = (m_rotation * m_xAxis);
    // float tmpY = tmpX.y;
    // tmpX.y = tmpX.z;
    // tmpX.z = tmpY;

    switch(axis) {
        case ACTION::ACCEL:
            m_position +=  (m_rotation * m_yAxis) * -speed;
            tmpX.print();
            break;
        case ACTION::STRAFE:
            m_position +=  (m_rotation * m_xAxis) * speed;
            break;
        case ACTION::LIFT:
            m_position += (m_rotation * m_zAxis) * speed;
            break;
        default:
            break;
    }
}

void Model::computeMatrix()
{
	// TODO:
    // Compute the transformation matrix for this object
	// according to the current position and rotation
	// state. Use the []-operator of the matrix class 
	// to set the according values based on the local
	// coordinate system base. Remember that the internal
	// values are accessed in C-order (row major)!

    m_transformation = m_rotation.toMatrix();

    m_transformation[0][3] = m_position.x;
    m_transformation[1][3] = m_position.y;
    m_transformation[2][3] = m_position.z;


    m_transformation.print();

    
}

void Model::printModelInformation()
{
    std::cout << "Model statistics: " << std::endl;
    std::cout << "Num vertices: " << m_numVertices << std::endl;
    std::cout << "Num faces:    " << m_numFaces << std::endl;
}

void Model::printBuffers()
{
    for(int i = 0; i < m_numVertices; i++)
    {
        std::cout << "v: " << m_vertexBuffer[3 * i]     << " "
                           << m_vertexBuffer[3 * i + 1] << " " 
                           << m_vertexBuffer[3 * i + 2] << std::endl;  
    }

    for(int i = 0; i < m_numFaces; i++)
    {
        std::cout << "f: " << m_indexBuffer[3 * i]     << " "
                           << m_indexBuffer[3 * i + 1] << " " 
                           << m_indexBuffer[3 * i + 2] << std::endl;  
    }
}

void Model::render()
{
    // Compute transformation matrix
	computeMatrix();

	// Push old transformation of the OpenGL matrix stack and
	// start rendering the mesh in according to the
	// internal transformation matrix
	glPushMatrix();
    m_transformation.transpose();
	glMultMatrixf(m_transformation.getData());
    m_transformation.transpose();

	// Render mesh
	for(int i = 0; i < m_numFaces; i++)
	{
		// Get position og current triangle in buffer
		int index = 3 * i;

		// Get vertex indices of triangle vertices
		int a = 3 * m_indexBuffer[index];
		int b = 3 * m_indexBuffer[index + 1];
		int c = 3 * m_indexBuffer[index + 2];

		// Render wireframe model
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(m_vertexBuffer[a], m_vertexBuffer[a + 1], m_vertexBuffer[a + 2]);
		glVertex3f(m_vertexBuffer[b], m_vertexBuffer[b + 1], m_vertexBuffer[b + 2]);
		glVertex3f(m_vertexBuffer[c], m_vertexBuffer[c + 1], m_vertexBuffer[c + 2]);
		glEnd();

	}

	// Pop transformation matrix of this object
	// to restore the previous state of the OpenGL
	// matrix stack
	glPopMatrix();
}

Model::~Model()
{
    if(m_vertexBuffer)
    {
        delete[] m_vertexBuffer;
    }

    if(m_indexBuffer)
    {
        delete[] m_indexBuffer;
    }
}

} // namespace asteroids 
