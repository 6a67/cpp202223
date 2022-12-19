/*
 *  Asteroid.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "Asteroid.hpp"
#include "math/Randomizer.hpp"

namespace asteroids
{

Asteroid::Asteroid(TexturedMesh* mesh, Vector3f start_position, float scale)
{
    initTransformations();

    // Save initial position
    m_position  = start_position;
    m_mesh      = mesh;
    m_scale     = scale;

    //Randomize Heading
    rotate(PITCH, Randomizer::instance()->getRandomNumber(0, 3.14159265));
    rotate(YAW  , Randomizer::instance()->getRandomNumber(0, 3.14159265));
    rotate(ROLL , Randomizer::instance()->getRandomNumber(0, 3.14159265));

    computeMatrix();
}

Asteroid& Asteroid::operator=( Asteroid& other )
{
	if(&other != this)
	{
		m_position = other.m_position;
		m_mesh = new TexturedMesh(*other.m_mesh);
		m_scale = other.m_scale;
        m_rotation = other.m_rotation;
        m_xAxis = other.m_xAxis;
        m_yAxis = other.m_yAxis;
        m_zAxis = other.m_zAxis;
	}
	return *this;
}


Asteroid::Asteroid(const Asteroid& other)
{
    cout << "COPY" << endl;
	m_position = other.m_position;
	m_mesh = new TexturedMesh(*other.m_mesh);
	m_scale = other.m_scale;
    m_rotation = other.m_rotation;
    m_xAxis = other.m_xAxis;
    m_yAxis = other.m_yAxis;
    m_zAxis = other.m_zAxis;
}

Asteroid::Asteroid()
{
    m_mesh = 0;
}

void Asteroid::render()
{
    // Compute transformation matrix
    computeMatrix();

    // Push matrix and set transformation and scaling
    glPushMatrix();
    glMultMatrixf(m_transformation.getData());
    
    glScalef(m_scale, m_scale, m_scale);
    if(m_mesh)
    {
        m_mesh->render();
    }
    glPopMatrix();
}

Asteroid::~Asteroid()
{
    cout << "DELETE" << endl;
    if (m_mesh)
    {
        delete m_mesh;
    }
}

} // namespace asteroids
