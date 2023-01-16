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

namespace asteroids
{

AsteroidField::AsteroidField(int quantity, const std::string& filename, float rangemax, float sizemin, float sizemax)
{
 	// Generate asteroids
	for(int i = 0; i < quantity; i++)
	{
	   TexturedMesh::Ptr mesh = std::static_pointer_cast<TexturedMesh>(TriangleMeshFactory::instance().getMesh(filename));
	   asteroids.push_back(Asteroid(
			mesh, Randomizer::instance()->getRandomVertex(rangemax), Randomizer::instance()->getRandomNumber(sizemin, sizemax)));
	}
}

AsteroidField::~AsteroidField()
{
	//asteroids.for_each(deleteAsteroid);
	
}

void AsteroidField::render()
{
	for(auto& t : asteroids)
	{
		t.render();
	}

}

} // namespace asteroids
