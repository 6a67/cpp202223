#include "Circle.hpp"

namespace asteroids
{

    Circle::Circle(MainWindow* mainWindow, float x, float y, float radius, int segments):
        Renderable2D(mainWindow)
    {
        m_x = x;
        m_y = y;
        m_radius = radius;
        m_segments = segments;
    }

    void Circle::render()
    {
        Renderable2D::begin2DRender();

        float theta            = 2 * 3.1415926 / float(m_segments);
        float tangetial_factor = tanf(theta);  // calculate the tangential factor

        float radial_factor = cosf(theta);  // calculate the radial factor

        float x = m_radius;  // we start at angle = 0

        float y = 0;

        glBegin(GL_LINE_LOOP);
        for (int ii = 0; ii < m_segments; ii++)
        {
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(x + m_x, y + m_y);  // output vertex

            // calculate the tangential vector
            // remember, the radial vector is (x, y)
            // to get the tangential vector we flip those coordinates and negate one of them

            float tx = -y;
            float ty = x;

            // add the tangential vector

            x += tx * tangetial_factor;
            y += ty * tangetial_factor;

            // correct using the radial factor

            x *= radial_factor;
            y *= radial_factor;
        }

        glEnd();

        Renderable2D::end2DRender();
    }


}  // namespace asteroids