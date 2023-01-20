#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <list>
#include "math/Vector.hpp"
#include <boost/graph/adjacency_list.hpp>


namespace asteroids
{

class PathPlanner
{
public:
    /**
     * @brief Initialzes tha pathfinder with a filename, which contains information about the graph
     *
     * @param mapfile   A file containing the representation of an graph
     *                  used for navigatuib
     */
    PathPlanner(std::string mapfile);

    /**
     * @brief Calculates a shortest path with the A*-Algorithm
     *
     * @param position Startposition of the ship
     * @param s Start of the path
     * @param e End of the path
     *
     * @return A shortest path from s to e
     */

    std::list<Vector<float>> getPath(Vector<float> position, std::string s, std::string e);

    typedef boost::adjacency_list<boost::vecS,
                                  boost::vecS,
                                  boost::undirectedS,
                                  boost::no_property,
                                  boost::property<boost::edge_weight_t, float>>
        Graph;

    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<Graph>::edge_descriptor   Edge;
    typedef float                                         CostType;


private:
    // vector of tuples in the format (x, y, z)
    std::vector<Vector3f> m_nodes;

    // vectors of edges in the format (from, to)
    std::vector<Vector2i> m_edges;

    Graph m_graph;

    // map that maps pos of vertex to name
    // only needed for additional route output
    std::map<int, std::string> m_posToName;

    // map that maps name of the planet to its vertex number given by boost
    std::map<std::string, Vertex> m_nameToPos;

    // map that maps name of the planet to the index of the vector
    // needed to look up the planets position in m_nodes
    std::map<std::string, int> m_nameToIndex;

    // this is where the values of the edges for the graph are stored
    boost::property_map<Graph, boost::edge_weight_t>::type m_weightmap
        = boost::get(boost::edge_weight, m_graph);

    /**
     * @brief Helper function that moves the starting planet to the center
     */
    void positionHelper(std::string s);

    /**
     * @brief Helper function for printing the route
     */
    void printRoute(std::list<Vector<float>> solutionPath);
};

}  // namespace asteroids

#endif
