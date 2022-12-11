#include "Sphere.hpp"

namespace asteroids
{

Sphere::Sphere(const Vector& position, float radius, int numSides, int numStack )
{
    m_position = position;
    m_radius = radius;
    m_numSides = numSides;
    m_numStacks = numStack;
}

void Sphere::render()
{
    float  curRadius, curTheta, curRho, deltaTheta, deltaRho, curX, curY, curZ;
    int    curStack, curSlice, numVerts = (m_numStacks - 1) * m_numSides;
    Vector points[numVerts];
    int    curVert = 0;
    int    t;

    deltaTheta = (2 * M_PI) / m_numSides;
    deltaRho   = M_PI / m_numStacks;

    for (curStack = 1; curStack < m_numStacks; curStack++)
    {
        curRho    = (3.141 / 2.0) - curStack * deltaRho;
        curY      = sin(curRho) * m_radius;
        curRadius = cos(curRho) * m_radius;
        for (curSlice = 0; curSlice < m_numSides; curSlice++)
        {
            curTheta          = curSlice * deltaTheta;
            curX              = curRadius * cos(curTheta);
            curZ              = -curRadius * sin(curTheta);
            points[curVert++] = Vector(curX, curY, curZ);
        }
    }

    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0, 1, 0);
    glVertex3d(0, m_radius, 0);
    for (t = 0; t < m_numSides; t++)
    {
        curX = points[t].x;
        curY = points[t].y;
        curZ = points[t].z;
        glNormal3d(curX, curY, curZ);
        glVertex3d(curX, curY, curZ);
    }
    curX = points[0].x;
    curY = points[0].y;
    curZ = points[0].z;
    glNormal3d(curX, curY, curZ);
    glVertex3d(curX, curY, curZ);
    glEnd();

    int vertIndex;
    for (curStack = 0; curStack < m_numStacks - 2; curStack++)
    {
        vertIndex = curStack * m_numSides;
        glBegin(GL_QUAD_STRIP);
        for (curSlice = 0; curSlice < m_numSides; curSlice++)
        {
            glNormal3d(points[vertIndex + curSlice].x,
                       points[vertIndex + curSlice].y,
                       points[vertIndex + curSlice].z);
            glVertex3d(points[vertIndex + curSlice].x,
                       points[vertIndex + curSlice].y,
                       points[vertIndex + curSlice].z);

            glNormal3d(points[vertIndex + m_numSides + curSlice].x,
                       points[vertIndex + m_numSides + curSlice].y,
                       points[vertIndex + m_numSides + curSlice].z);
            glVertex3d(points[vertIndex + m_numSides + curSlice].x,
                       points[vertIndex + m_numSides + curSlice].y,
                       points[vertIndex + m_numSides + curSlice].z);
        }
        glNormal3d(points[vertIndex].x, points[vertIndex].y, points[vertIndex].z);
        glVertex3d(points[vertIndex].x, points[vertIndex].y, points[vertIndex].z);
        glNormal3d(points[vertIndex + m_numSides].x,
                   points[vertIndex + m_numSides].y,
                   points[vertIndex + m_numSides].z);
        glVertex3d(points[vertIndex + m_numSides].x,
                   points[vertIndex + m_numSides].y,
                   points[vertIndex + m_numSides].z);
        glEnd();
    }

    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0, -1, 0);
    glVertex3d(0, -m_radius, 0);
    for (t = 0; t < m_numSides - 1; t++)
    {
        curX = points[numVerts - 1 - t].x;
        curY = points[numVerts - 1 - t].y;
        curZ = points[numVerts - 1 - t].z;
        glNormal3d(curX, curY, curZ);
        glVertex3d(curX, curY, curZ);
    }
    curX = points[numVerts - 1].x;
    curY = points[numVerts - 1].y;
    curZ = points[numVerts - 1].z;
    glNormal3d(curX, curY, curZ);
    glVertex3d(curX, curY, curZ);
    glEnd();
}

}