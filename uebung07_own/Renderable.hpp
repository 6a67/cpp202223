#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

/* OpenGL / glew Headers */
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

namespace asteroids
{

class Renderable
{
public:
    virtual void render() = 0;

private:
// Dimensions
    float m_w;
    float m_h;

};

} // namespace asteroids
#endif // RENDERABLE_HPP