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

Model::Model(const std::string& filename)
{
    LoadPLY(
        filename, 
        m_vertexBuffer, m_indexBuffer, 
        m_numVertices, m_numFaces);
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
    for (int i = 0; i < m_numFaces; i++)
    {
        /* Get position og current triangle in buffer */
        int index = 3 * i;

        /* Get vertex indices of triangle vertices */
        int a = 3 * m_indexBuffer[index];
        int b = 3 * m_indexBuffer[index + 1];
        int c = 3 * m_indexBuffer[index + 2];

        //printf("%d %d %d\n", a, b, c);

        /* Render wireframe model */
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(m_vertexBuffer[a], m_vertexBuffer[a + 1], m_vertexBuffer[a + 2]);
        glVertex3f(m_vertexBuffer[b], m_vertexBuffer[b + 1], m_vertexBuffer[b + 2]);
        glVertex3f(m_vertexBuffer[c], m_vertexBuffer[c + 1], m_vertexBuffer[c + 2]);
        glEnd();
        glFlush();
    }
}

int Model::getNumVertices()
{
    return m_numVertices;
}

int Model::getNumFaces()
{
    return m_numFaces;
}

float Model::getVertexValue(int index)
{
    return m_vertexBuffer[index];
}

int Model::getIndexValue(int index)
{
    return m_indexBuffer[index];
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
