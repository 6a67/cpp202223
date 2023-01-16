#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <list>
#include "math/Vector.hpp"


namespace asteroids
{


class PathPlanner {
  public:
    /**
     * @brief Initialzes tha pathfinder with a filename, which contains information about the graph
     * 
     * @param mapfile   A file containing the representation of an graph
     *                  used for navigatuib
     */
    PathPlanner (std::string mapfile);

    /**
     * @brief Calculates a shortest path with the A*-Algorithm
     * 
     * @param position Startposition of the ship
     * @param s Start of the path
     * @param e End of the path
     * 
     * @return A shortest path from s to e
     */

    std::list<Vector<float> > getPath(Vector<float> position, std::string s, std::string e);
  
};

}



#endif
