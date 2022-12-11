//
// Created by sascha on 10.12.22.
//

#ifndef CPP18_ASTEROIDS_RENDERABLE3D_HPP
#define CPP18_ASTEROIDS_RENDERABLE3D_HPP

#include "Renderable.hpp"

namespace asteroids
{
class Renderable3D : public Renderable
{
public:
    virtual void render() = 0;
};
} // namespace asteroids

#endif //CPP18_ASTEROIDS_RENDERABLE3D_HPP
