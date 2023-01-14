#include "Bullet.hpp"
#include <GL/glut.h>
#include <thread>
#include <chrono>

namespace asteroids
{

Bullet::Bullet(const Vector3f& fighter_position, const Vector3f fighter_axis):
    m_position(fighter_position),
    m_axis(fighter_axis),
    m_alive(true),
    m_sphere(fighter_position, 10, 10)
{
}

Bullet::~Bullet()
{

}

void Bullet::run()
{
    for(int i = 0; i < m_lifetime; i++)
    {
        m_position += m_axis;
        m_sphere.setPosition(m_position);
        std::this_thread::sleep_for(m_sleeptime);
    }
    m_alive = false;
}

void Bullet::start()
{
    m_thread = std::thread(&Bullet::run, this);
}

void Bullet::stop()
{
    if(m_thread.joinable())
    {
        m_thread.join();
    }
    m_alive = false;
}

bool Bullet::isAlive()
{
    return m_alive;
}

void Bullet::render()
{
    m_sphere.render();
}


} // namespace asteroids