#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <fstream>

#include "PathPlanner.hpp"

namespace asteroids
{

std::list<Vector<float> > PathPlanner::getPath(Vector<float> position, std::string s, std::string e)
{
    // TODO: Plan a path from s to e using the A* implementaion
    // of the Boost Graph Library. Add the positions of the 
    // visited nodes of the solution to this list.
    std::list<Vector<float> > solutionPath;

    return solutionPath;
}


PathPlanner::PathPlanner (std::string mapfile) 
{
    // TODO: Parse file and build graph representation as 
    // for planning with BGL.

   
}
    
}
