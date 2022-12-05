/**
 * @brief renderSphere  Render a sphere around the origin of the coordinate system
 * @param m_radius      The sphere's radius
 * @param m_numStacks   Number of vertical intersections
 * @param m_numSides    Number of horizonten intersections
 */
void renderSphere(float m_radius, int m_numStacks, int m_numSides)
{

    float curRadius, curTheta, curRho, deltaTheta, deltaRho, curX,curY,curZ;
    int curStack, curSlice, numVerts = (m_numStacks-1)*m_numSides;
    Vector points[numVerts];
    int curVert = 0;
    int t;

    deltaTheta = (2*M_PI) / m_numSides;
    deltaRho = M_PI / m_numStacks;

        for (curStack=1; curStack< m_numStacks; curStack++)
        {
            curRho = (3.141/2.0) - curStack*deltaRho;
            curY = sin(curRho) * m_radius;
            curRadius = cos(curRho) * m_radius;
            for (curSlice=0; curSlice< m_numSides; curSlice++)
            {
                curTheta = curSlice * deltaTheta;
                curX = curRadius * cos(curTheta);
                curZ = -curRadius * sin(curTheta);
                points[curVert++] = Vector(curX,curY,curZ);
            }
        }

        glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0,1,0);
        glVertex3d(0, m_radius,0);
        for (t=0; t< m_numSides; t++)
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
    for (curStack=0; curStack< m_numStacks-2; curStack++)
    {
        vertIndex = curStack * m_numSides;
        glBegin(GL_QUAD_STRIP);
            for (curSlice=0; curSlice< m_numSides; curSlice++)
            {
                glNormal3d(points[vertIndex+curSlice].x, points[vertIndex+curSlice].y, points[vertIndex+curSlice].z);
                glVertex3d(points[vertIndex+curSlice].x, points[vertIndex+curSlice].y, points[vertIndex+curSlice].z);

                glNormal3d(points[vertIndex+ m_numSides + curSlice].x, points[vertIndex+m_numSides+curSlice].y, points[vertIndex+m_numSides+curSlice].z);
                glVertex3d(points[vertIndex+ m_numSides + curSlice].x, points[vertIndex+m_numSides+curSlice].y, points[vertIndex+m_numSides+curSlice].z);
            }
            glNormal3d(points[vertIndex].x, points[vertIndex].y, points[vertIndex].z);
            glVertex3d(points[vertIndex].x, points[vertIndex].y, points[vertIndex].z);
            glNormal3d(points[vertIndex+ m_numSides].x, points[vertIndex+m_numSides].y, points[vertIndex+m_numSides].z);
            glVertex3d(points[vertIndex+ m_numSides].x, points[vertIndex+m_numSides].y, points[vertIndex+m_numSides].z);
        glEnd();
    }

    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0,-1,0);
        glVertex3d(0,- m_radius,0);
        for (t=0; t< m_numSides-1; t++)
        {
            curX = points[numVerts-1-t].x;
            curY = points[numVerts-1-t].y;
            curZ = points[numVerts-1-t].z;
            glNormal3d(curX, curY, curZ);
            glVertex3d(curX, curY, curZ);
        }
            curX = points[numVerts-1].x;
            curY = points[numVerts-1].y;
            curZ = points[numVerts-1].z;
        glNormal3d(curX, curY, curZ);
        glVertex3d(curX, curY, curZ);
    glEnd();
}

/**
 * @brief renderRectangle   Renders a rectangle
 * @param m_x               X coordinate of upper left corner
 * @param m_y               Y coordinate of upper left corner
 * @param m_w               Width
 * @param m_h               Height
 */
void renderRectangle(float m_x, float m_y, float m_w, float m_h)
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(m_x, m_y);
    glVertex2d(m_x + m_w, m_y);
    glVertex2d(m_x + m_w, m_y + m_h);
    glVertex2d(m_x, m_y + m_h);
    glEnd();
}

/**
 * @brief renderCircle      Renders a circle
 * @param m_x               X coordinate of the origin
 * @param m_y               Y coordinate of the origin
 * @param m_radius          Radius
 * @param m_segments        Number of line segments to approximate the
 *                          circle
 */
void renderCircle(float m_x, float m_y, float m_radius, int m_segments)
{
    float theta = 2 * 3.1415926 / float(m_segments);
    float tangetial_factor = tanf(theta);//calculate the tangential factor

    float radial_factor = cosf(theta);//calculate the radial factor

    float x = m_radius;//we start at angle = 0

    float y = 0;

    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < m_segments; ii++)
    {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x + m_x, y + m_y);//output vertex

        //calculate the tangential vector
        //remember, the radial vector is (x, y)
        //to get the tangential vector we flip those coordinates and negate one of them

        float tx = -y;
        float ty = x;

        //add the tangential vector

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        //correct using the radial factor

        x *= radial_factor;
        y *= radial_factor;
    }

    glEnd();
}
