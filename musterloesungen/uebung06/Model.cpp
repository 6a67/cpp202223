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

	// Set tranformation matrix to unit matrix
	for(int i = 0; i < 16; i++)
	{
		m_transformation[i] = 0.0f;
	}
	m_transformation[0 ] = 1.0f;
	m_transformation[5 ] = 1.0f;
	m_transformation[10] = 1.0f;
	m_transformation[15] = 1.0f;
 }

void Model::rotate(ACTION axis, float s)
{
    Quaternion nq;

	// Get the wanted operation and calculate the new coordinates
	switch(axis)
	{
	case YAW:
		nq.fromAxis(m_yAxis, s);
		m_xAxis = nq * m_xAxis;
		m_zAxis = nq * m_zAxis;
		break;

	case PITCH:
		nq.fromAxis(m_zAxis, s);
		m_xAxis = nq * m_xAxis;
		m_yAxis = nq * m_yAxis;
		break;

	case ROLL:
		nq.fromAxis(m_xAxis, s);
		m_yAxis = nq * m_yAxis;
		m_zAxis = nq * m_zAxis;
		break;
    default:
        return;
	}

	// Update mesh rotation 
	m_rotation = m_rotation * nq;
}

void Model::move(ACTION axis, float speed)
{
    Vector direction;

	// Determine the correct axis of the local system
	switch(axis)
	{
	case ACCEL:
		direction = m_xAxis;
		break;
	case STRAFE:
		direction = m_yAxis;
		break;
	case LIFT:
		direction = m_zAxis;
        break;
    default:
        return;
	}

	// Update mesh position
	m_position = m_position + direction * speed;
}

void Model::computeMatrix()
{
    // Compute the transformation matrix for this object
	// according to the current position and rotation
	// state
	m_transformation[0]  = m_yAxis[0];
	m_transformation[1]  = m_yAxis[1];
	m_transformation[2]  = m_yAxis[2];

	m_transformation[4]  = m_xAxis[0];
	m_transformation[5]  = m_xAxis[1];
	m_transformation[6]  = m_xAxis[2];

	m_transformation[8]  = m_zAxis[0];
	m_transformation[9]  = m_zAxis[1];
	m_transformation[10] = m_zAxis[2];

	m_transformation[12] = m_position[0];
	m_transformation[13] = m_position[1];
	m_transformation[14] = m_position[2];
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
	glMultMatrixf(m_transformation.getData());

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
