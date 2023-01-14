/*
 *  Bullet.hpp
 *
 *  Created on: Jan. 06 2019
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2019 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "../math/Vector.hpp"
#include "Sphere.hpp"
#include <thread>
#include <memory>
#include <chrono>

namespace asteroids
{

/**
 * @brief Renders a Bullet
 */
class Bullet
{

public:

    // Alias Ptr for a shared pointer to a Bullet
    // shared_ptr is a smart pointer that counts the references and automatically deletes the object when the last reference is deleted
    using Ptr = std::shared_ptr<Bullet>;

    /**
     * @brief Contructor. Build a bullet on the given Fighter's
     *                      position. The bullet will move on the
     *                      given axis.
     * @param   fighter_position   Position of the fighter that shoots this bullet
     * @param   fighter_axis   Axis the bullet will move on
     */
    Bullet(const Vector3f& fighter_position, const Vector3f fighter_axis);

    ~Bullet();

    /**
     * @brief Moves the bullet until it's lifetime is over.
     */
	void run();

	/**
	 * @brief Starts bullet movement
	 */
	void start();


	/*
	 * @brief Stops bullet movement
     */
	void stop();
    
    /**
     * @brief Renders the bullet via glutSolidSphere.
     */
	void render();

    /**
     * @brief Returns the status of this bullet.
     * @return false, if the bullet's lifetime is over and true otherwise
     */
	bool isAlive();

private:

    // TODO: ADD ADDITIONAL CLASS ELEMENTS TO IMPLEMENT
    // THE REQUIRED FUCTIONALITIES

    /// Position of the bullet
    Vector3f m_position;

    /// Axis the bullet will move on
    Vector3f m_axis;

    /// Status of the bullet
    bool m_alive;

    /// Sleeptime
    std::chrono::duration<int, std::micro> m_sleeptime = std::chrono::microseconds(1000);

    /// Lifetime of the bullet (in this case 10 seconds)
    int m_lifetime = 10000;

    /// Thread to move the bullet
    std::thread m_thread;

    /// Sphere objet to render the bullet
    Sphere m_sphere;
};

} // namespace asteroids


#endif /* BULLET_HPP_ */
