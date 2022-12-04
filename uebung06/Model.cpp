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
    m_numFaces     = 0;
    m_numVertices  = 0;
    m_vertexBuffer = 0;
    m_indexBuffer  = 0;

    // Setup rotation and position
    m_xAxis    = Vector(1.0, 0.0, 0.0);
    m_yAxis    = Vector(0.0, 1.0, 0.0);
    m_zAxis    = Vector(0.0, 0.0, 1.0);
    m_position = Vector(0.0, 0.0, 0.0);

    // Init initial position
    initTransformations();
}

Model::Model(const Model& other)
{
    m_numFaces     = other.m_numFaces;
    m_numVertices  = other.m_numVertices;
    m_vertexBuffer = new float[3 * m_numVertices];
    m_indexBuffer  = new int[3 * m_numFaces];

    m_xAxis          = other.m_xAxis;
    m_yAxis          = other.m_yAxis;
    m_zAxis          = other.m_zAxis;
    m_position       = other.m_position;
    m_rotation       = other.m_rotation;
    m_transformation = other.m_transformation;
}

Model::Model(int* faces, float* vertices, int a, int b)
{
    // Save mesh information and buffers
    m_numFaces     = a;
    m_numVertices  = b;
    m_vertexBuffer = vertices;
    m_indexBuffer  = faces;

    // Init initial position
    initTransformations();
}

Model::Model(const std::string& filename)
{
    LoadPLY(filename, m_vertexBuffer, m_indexBuffer, m_numVertices, m_numFaces);

    // Init initial position
    initTransformations();
}

void Model::initTransformations()
{
    // Setup rotation and position
    m_xAxis    = Vector(1.0, 0.0, 0.0);
    m_yAxis    = Vector(0.0, 1.0, 0.0);
    m_zAxis    = Vector(0.0, 0.0, 1.0);
    m_position = Vector(0.0, 0.0, 0.0);
    m_rotation.fromAxis(Vector(0.0, 0.0, 1.0), 0.0f);
}

void Model::rotate(ACTION axis, float s)
{
    switch (axis)
    {
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
            std::cout << axis << std::endl;
            break;
    }
}

void Model::move(ACTION axis, float speed)
{
    switch (axis)
    {
        case ACTION::ACCEL:
            m_position += (m_rotation * m_yAxis) * -speed;
            break;
        case ACTION::STRAFE:
            m_position += (m_rotation * m_xAxis) * speed;
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
    // m_rotation stores all the rotation information of the model
    // convert it to a 4x4 matrix and store it in m_transformation
    m_transformation = m_rotation.toMatrix();


    // m_transformation stores the rotation matrix of the model
    // apply the translation to the model by adding the position
    m_transformation[0][3] = m_position.x;
    m_transformation[1][3] = m_position.y;
    m_transformation[2][3] = m_position.z;
}

void Model::printModelInformation()
{
    std::cout << "Model statistics: " << std::endl;
    std::cout << "Num vertices: " << m_numVertices << std::endl;
    std::cout << "Num faces:    " << m_numFaces << std::endl;
}

void Model::printBuffers()
{
    for (int i = 0; i < m_numVertices; i++)
    {
        std::cout << "v: " << m_vertexBuffer[3 * i] << " " << m_vertexBuffer[3 * i + 1] << " "
                  << m_vertexBuffer[3 * i + 2] << std::endl;
    }

    for (int i = 0; i < m_numFaces; i++)
    {
        std::cout << "f: " << m_indexBuffer[3 * i] << " " << m_indexBuffer[3 * i + 1] << " "
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
    // glMultMatrixf expects the matrix to be in column-major
    // transposing the matrix converts the row-major to column-major
    m_transformation.transpose();
    glMultMatrixf(m_transformation.getData());
    // after applying the column-major matrix, transpose it back
    m_transformation.transpose();

    // Render mesh
    for (int i = 0; i < m_numFaces; i++)
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
    if (m_vertexBuffer)
    {
        delete[] m_vertexBuffer;
    }

    if (m_indexBuffer)
    {
        delete[] m_indexBuffer;
    }
}

}  // namespace asteroids
