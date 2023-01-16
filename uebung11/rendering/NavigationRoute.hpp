/**
 * NavigationRoute.h
 *
 *  @date 22.01.2012
 *  @author Thomas Wiemann
 */

#ifndef NAVIGATIONROUTE_H_
#define NAVIGATIONROUTE_H_

// Project includes
#include "math/Vector.hpp"
#include "Renderable.hpp"

// OpenGL stuff
#include <GL/glew.h>

// STL stuff
#include <list>
#include <memory>

using std::list;

namespace asteroids
{

class NavigationRoute : public Renderable
{
public:
    using Ptr = std::shared_ptr<NavigationRoute>;
 
    /// Initialises a route of vectors that 
    /// represent navigation goals
    NavigationRoute(list<Vector<float> > path);

    virtual ~NavigationRoute();

    /// Renders the positions of the goals in the path
    /// and their connections
    virtual void render();

private:

    /// Renders a sphere
    void renderWireSphere(float radius, int n_paral, int n_merid);

    GLuint          m_pathList;
    GLuint          m_navPointList;
   
};

} // namespace asteroids

#endif /* NAVIGATIONROUTE_H_ */
