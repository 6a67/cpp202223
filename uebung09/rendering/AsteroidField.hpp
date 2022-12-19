/*
 *  AsteroidField.hpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef STARFIELD_HPP_
#define STARFIELD_HPP_

#include <cmath>
#include <algorithm>
#include <vector>

#include "Renderable3D.hpp"
#include "Asteroid.hpp"
#include "math/Vector.hpp"

using std::for_each;
using std::generate;
using std::vector;

// #include <list>
#include "util/List.hpp"

namespace asteroids
{

/**
 * @brief   Representatio of an asteroid field
 */
class AsteroidField : public Renderable3D
{
public:
    /**
     * @brief   Creates an asteroid field with n asteroids in it
     */
    AsteroidField(int n, const std::string& filename, float rangemax, float sizemin, float sizemax);

    /**
     * @brief   Dtor.
     */
    virtual ~AsteroidField();

    /**
     * @brief   Renders all asteroids
     */
    void render();

private:
    /// The asteroids in the field
    List<Asteroid> asteroids;
};

}

#endif
