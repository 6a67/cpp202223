/**
 * @file
 * Bullet.hpp
 *
 */

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "TriangleMesh.hpp"
#include "Sphere.hpp"

#include <thread>
#include <chrono>
#include <memory>

namespace asteroids
{

/**
 * @brief Renders a Bullet
 */
class Bullet: public TriangleMesh
{

public:

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

    // Lifetime, i.e., how many timesteps the bullet visible
	static const int m_lifetime = 9000;

	// True, if the bullet's lifetime isn't over yet
	bool m_alive;

	// Flight direction of the bullet
    Vector3f m_fighterAxis;

    /// Thread that runs the bullet
    std::thread m_thread;
    
    /// Sleeptime in main loop
    std::chrono::milliseconds m_sleepDuration;

    /// Sphere objet to render the bullet
    Sphere m_sphere;
};

} // namespace asteroids


#endif /* BULLET_HPP_ */
