#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <list>
#include "math/Vector.hpp"
#include <boost/graph/adjacency_list.hpp>


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

/*    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
    boost::property<boost::vertex_name_t, std::string>,
    boost::property<boost::edge_weight_t, float > > Graph;*/

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property,
                                    boost::property<boost::edge_weight_t, float> > Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;


private:

    // vector with tuple of size 4 (name, x, y, z) that is needed for calculating the distance
    // not tuple anymore TODO
    std::vector<Vector3f> m_nodes;

    // vector with tuple of size 2 (from, to)
    // not tuple anymore TODO
    std::vector<Vector2i> m_edges;

    // map with name as key and x,y,z tuple as value
//    std::map<std::string, std::tuple<float, float, float>> m_nodeMap;

    Graph m_graph;

//    boost::property_map<Graph, boost::vertex_name_t>::type m_planet_names = boost::get(boost::vertex_name, m_graph);

    // map that maps pos of vertex to name
    std::map<int, std::string> m_posToName;

    // map that maps name of the planet to its vertex number given by boost
    std::map<std::string, Vertex> m_nameToPos;

    // map that maps name of the planet to the index of the vector
    std::map<std::string, int> m_nameToIndex;

    boost::property_map<Graph, boost::edge_weight_t>::type m_weightmap = boost::get(boost::edge_weight, m_graph);


    void positionHelper(std::string s);

    void printRoute(std::list<Vector<float> > solutionPath);

};



}



#endif
