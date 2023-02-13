/**
 * Camera.cpp
 *
 *  @date 27.11.2011
 *  @author Thomas Wiemann
 */

#include "Camera.hpp"

#ifdef __APPLE__
#include <OpenGL/gl.h>         
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


namespace asteroids
{

Camera::Camera()
    : m_baseX(1.0, 0.0, 0.0), m_baseY(0.0, 1.0, 0.0), m_baseZ(0.0, 0.0, 1.0)
{
	m_px =          0.0;
	m_py =          0.0;
	m_pz =          0.0;

	m_ix =          0.0;
	m_iy =          20.0;
	m_iz =          100.0;
	m_turnSpeed =   0.02;
	m_speed =       20;

	m_rotX =        0.0;
	m_rotY =        0.0;

}

Camera::Camera(float x, float y, float z)
     : m_baseX(1.0, 0.0, 0.0), m_baseY(0.0, 1.0, 0.0), m_baseZ(0.0, 0.0, 1.0)
{
	m_px = 0.0;
	m_py = 0.0;
	m_pz = 0.0;
	m_lx = m_ly = 0.0;
	m_lz = 0.0;
	m_speed = m_turnSpeed = 0.2;
	m_ix = x;
	m_iy = y;
	m_iz = z;

	m_rotX = 0.0;
	m_rotY = 0.0;
}

void Camera::moveLeft()
{
	m_px -= m_speed * sin(PH - m_rotY);
	m_pz -= m_speed * cos(PH - m_rotY);
}

void Camera::moveRight()
{
	m_px += m_speed * sin(PH + m_rotY);
	m_pz += m_speed * cos(PH + m_rotY);
}

void Camera::moveForward()
{
	m_px += m_speed * sin(m_rotY);
	m_pz += m_speed * cos(m_rotY);
}
void Camera::moveBackward()
{
	m_px -= m_speed * sin(m_rotY);
	m_pz -= m_speed * cos(m_rotY);
}

void Camera::turnUp()
{
	if(m_rotX < PH) 
	{
		m_rotX -= m_turnSpeed;

		// Transform base
//		Quaternion nq(m_baseX, -m_turnSpeed);
//		m_baseY = nq * m_baseY;
//		m_baseZ = nq * m_baseZ;
	}
}

void Camera::turnDown()
{
	if(m_rotX > -PH)
	{
		m_rotX += m_turnSpeed;

		//Transform base
//		Quaternion nq(m_baseX, m_turnSpeed);
//		m_baseY = nq * m_baseY;
//		m_baseZ = nq * m_baseZ;
	}
}

void Camera::turnLeft()
{
	m_rotY -= m_turnSpeed;

	//Transform base
	Quaternion nq(m_baseY, m_turnSpeed);
	m_baseX = nq * m_baseX;
	m_baseZ = nq * m_baseZ;
}

void Camera::turnRight()
{
	m_rotY += m_turnSpeed;

    //Transform base
    Quaternion nq(m_baseY, -m_turnSpeed);
    m_baseX = nq * m_baseX;
    m_baseZ = nq * m_baseZ;
}

void Camera::moveUp()
{
	m_py += m_speed;
}


void Camera::moveDown()
{
	m_py -= m_speed;
}

void Camera::applyRotationOnly()
{
    float lx =   sin(m_rotY);
    float lz = - cos(m_rotY);
    float ly =   sin(m_rotX);

    glLoadIdentity();
    gluLookAt(lx, ly, lz, 0, 0, 0, 0.0, 1.0, 0.0);
}

void Camera::setLocation(Vector<float> p, Vector<float> d, Vector<float> u, float above, float behind)
{

    // Clear matrix stack
    glLoadIdentity();

    Normal<float> direction = Normal<float>(d);
    Normal<float> up = Normal<float>(u);

    Vector<float> cam = p + up * above + direction * behind;
    Vector<float> pos = p + (up * above);

 /*   //m_list_pos.push_back(m_pos);
    m_list_cam.push_front(cam);
    m_list_up.push_front(up);
    m_list_pos.push_front(pos);

    //m_realpos = m_list_pos.front() - (m_list_up.front() * m_above);
    if(m_list_cam.size() > 5)
    {
        m_list_pos.pop_back();
        m_list_cam.pop_back();
        m_list_up.pop_back();
    }
    pos = m_list_pos.back();
    cam = m_list_cam.back();
    up = m_list_up.back();*/

    // Calc transformation Matrix
    gluLookAt(cam[0], cam[1], cam[2],
              pos[0], pos[1], pos[2],
               up[0] , up[1] , up[2]);

}

void Camera::apply()
{
    // Create position and look at vector
    m_lx = m_ix + m_px + sin(m_rotY);
    m_lz = m_iz - m_pz - cos(m_rotY);
    m_ly = m_iy + m_py + sin(m_rotX);

    // Clear matrix stack
    glLoadIdentity();

    // Calc transformation matrix
    gluLookAt(m_ix + m_px, m_iy + m_py, m_iz - m_pz,
            m_lx, m_ly, m_lz,
            0.0, 1.0, 0.0);
}


} // namespace asteroids
