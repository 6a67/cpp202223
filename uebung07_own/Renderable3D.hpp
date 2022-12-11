#ifndef RENDERABLE3D_HPP
#define RENDERABLE3D_HPP

#include "Renderable.hpp"

namespace asteroids
{

class Renderable3D : public Renderable
{
public:
    virtual void render() = 0;
};

} // namespace asteroids
#endif // RENDERABLE3D_HPP