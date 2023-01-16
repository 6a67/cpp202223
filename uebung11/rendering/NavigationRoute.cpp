/**
 * NavigationRoute.cpp
 *
 *  @date 22.01.2012
 *  @author Thomas Wiemann
 */

#include "NavigationRoute.hpp"

#include <iostream>
#include <cmath>

using std::endl;
using std::cout;

namespace asteroids
{

NavigationRoute::NavigationRoute(list<Vector<float> > path)
{
    // Iterator for path points
    list<Vector<float> >::iterator it;

    // Create a display list for the path
    m_pathList = glGenLists(1);
    glNewList(m_pathList, GL_COMPILE);
    glColor3f(1.0, 0.0, 0.0);
    // Draw path as thick line
    glBegin(GL_LINE_STRIP);
    for(it = path.begin(); it != path.end(); it++)
    {
        Vector<float> v = *it;
        glVertex3f(v[0], v[1], v[2]);

    }
    glEnd();
    glEndList();

    // Create a display list for the navigation points
    m_navPointList = glGenLists(1);
    glNewList(m_navPointList, GL_COMPILE);
    for(it = path.begin(); it != path.end(); it++)
    {
        Vector<float> v = *it;
        glColor3f(0.0, 1.0, 0.0);
        glPushMatrix();
        glTranslatef(v[0], v[1], v[2]);
        renderWireSphere(100, 10 ,10);
        glPopMatrix();
    }
    glEndList();
}

void NavigationRoute::render()
{
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(5.0);
    glCallList(m_pathList);
    glLineWidth(1.0);
    glCallList(m_navPointList);
    glEnable(GL_LIGHTING);
}

NavigationRoute::~NavigationRoute()
{
    // TODO Auto-generated destructor stub
}

void NavigationRoute::renderWireSphere(float radius, int n_paral, int n_merid)
{
    float x;
    float y;
    float z;

    for (float j = 0; j < M_PI; j += M_PI / (n_paral + 1))
    {
        glBegin(GL_LINE_LOOP);
        y =  static_cast<float>(radius * cos(j));
        
        for(float i = 0; i < 2 * M_PI; i += M_PI / 60)
        {
            x = static_cast<float>(radius * cos(i) * sin(j));
            z = static_cast<float>(radius * sin(i) * sin(j));
            glVertex3f(x, y, z);
        }

        glEnd();
    }

    for(float j = 0; j < M_PI; j += M_PI / n_merid)
    {
        glBegin(GL_LINE_LOOP);
        
        for(float i = 0; i < 2 * M_PI; i += M_PI / 60)
        {
            x = static_cast<float>(radius * sin(i) * cos(j));
            y = static_cast<float>(radius * cos(i));
            z = static_cast<float>(radius * sin(j) * sin(i));
            glVertex3f(x, y, z);
        }

        glEnd();
    }
}

} // namespace asteroids
