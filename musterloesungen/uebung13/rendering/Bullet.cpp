/**
 * Bullet.cpp
 *
 */

#include "Bullet.hpp"

namespace asteroids
{

Bullet::Bullet(const Vector3f& fighter_position, const Vector3f fighter_axis)
	: m_alive(true), m_sleepDuration(1), m_sphere(Vector3f(0, 0, 0), 10)
{
    // the bullet will move on this axis, it has to be reversed for the direction to be right    
    this->m_fighterAxis = fighter_axis * -1;

    // same position as the fighter
	m_position = fighter_position;
}

Bullet::~Bullet()
{
	stop();
}

bool Bullet::isAlive()
{
	return m_alive;
}

void Bullet::stop()
{
	// Signal last loop to thread
	m_alive = false;

	m_thread.join();
}

void Bullet::start()
{
	m_thread = std::thread(&Bullet::run, this);
}

void Bullet::run()
{
	int i = 0;
    // Modify the bullet's position until the lifetime is over
	while(i < m_lifetime && m_alive)
	{
		m_position = m_fighterAxis  + m_position;
		i++;
		std::this_thread::sleep_for(m_sleepDuration);
	}
	m_alive = false;
}

void Bullet::render()
{
    // Compute transformation matrix
	computeMatrix();
    // Push old transformation of the OpenGL matrix stack and
	// start rendering the bullet in according to the
	// internal transformation matrix
	glPushMatrix();
	glMultMatrixf(m_transformation.getData());
	
	m_sphere.render();

	// Pop transformation matrix of this object
	// to restore the previous state of the OpenGL
	// matrix stack
	glPopMatrix();
}

} // namespace asreroids

