//
// Created by sascha on 10.12.22.
//

#ifndef CPP18_ASTEROIDS_RENDERABLE_HPP
#define CPP18_ASTEROIDS_RENDERABLE_HPP

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

namespace asteroids
{
class Renderable
{
public:
    // Render function for the renderable object
    virtual void render() = 0;
};
}

#endif //CPP18_ASTEROIDS_RENDERABLE_HPP
