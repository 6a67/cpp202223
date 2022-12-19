/*
 *  AsteoridField.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "AsteroidField.hpp"
#include "math/Randomizer.hpp"
#include "rendering/Asteroid.hpp"
#include "io/TriangleMeshFactory.hpp"

namespace asteroids
{

AsteroidField::AsteroidField(
    int quantity, const std::string& filename, float rangemax, float sizemin, float sizemax)
{
    // Generate asteroids
    for (int i = 0; i < quantity; i++)
    {
        /// Get mesh from class TriangleMeshFactory and add new
        /// Asteroid to internal list

        // Randomize position
        float x = Randomizer::instance()->getRandomNumber(-rangemax, rangemax);
        float y = Randomizer::instance()->getRandomNumber(-rangemax, rangemax);
        float z = Randomizer::instance()->getRandomNumber(-rangemax, rangemax);

        // Randomize size
        float size = Randomizer::instance()->getRandomNumber(sizemin, sizemax);

        // Add asteroid to list
        asteroids.push_back(
            Asteroid((TexturedMesh*) TriangleMeshFactory::getInstance().getMesh(filename),
                     Vector3f(x, y, z),
                     size));
    }
}

AsteroidField::~AsteroidField()
{
    // asteroids.for_each(deleteAsteroid);
}

void AsteroidField::render()
{
    for (auto& t : asteroids)
    {
        t.render();
    }
}

}  // namespace asteroids
