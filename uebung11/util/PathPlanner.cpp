#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>
#include <sstream>
#include <boost/graph/astar_search.hpp>
#include "AStartVisitor.hpp"

#include "PathPlanner.hpp"

namespace asteroids
{

// heuristic function is specific to this graph and is therefore defined here
class distance_heuristic : public boost::astar_heuristic<PathPlanner::Graph, PathPlanner::CostType>
{
public:
    distance_heuristic(std::vector<Vector3f>& l, PathPlanner::Vertex goal)
    : m_location(l)
    , m_goal(goal)
    {
    }

    PathPlanner::CostType operator()(PathPlanner::Vertex u)
    {
        Vector3f goal    = m_location[m_goal];
        Vector3f current = m_location[u];
        Vector3f r       = goal - current;
        return sqrt(pow(r[0], 2) + pow(r[1], 2) + pow(r[2], 2));
    }

private:
    std::vector<Vector3f>& m_location;
    PathPlanner::Vertex    m_goal;
};


std::list<Vector<float>> PathPlanner::getPath(Vector<float> position, std::string s, std::string e)
{
    std::list<Vector<float>> solutionPath;
    positionHelper(s);

    // get vertex from name
    int start = m_nameToIndex[s];
    int end   = m_nameToIndex[e];

    // vector to store the found route
    std::vector<Vertex> path(num_vertices(m_graph));
    // vector to store the distances
    std::vector<PathPlanner::CostType> dist(num_vertices(m_graph));

    try
    {
        // does an astar search given the start vertex, the heuristic function and the visitor
        boost::astar_search(m_graph,
                            start,
                            distance_heuristic(m_nodes, end),
                            boost::predecessor_map(&path[0]).distance_map(&dist[0]).visitor(
                                AStarVisitor<Vertex, Graph>(end)));
    }
    catch (GoalException& goalException)
    {
        // found a path to the goal
        for (Vertex v = end;; v = path[v])
        {
            solutionPath.push_front(m_nodes[v]);
            if (path[v] == v)
            {
                break;
            }
        }
        printRoute(solutionPath);
        return solutionPath;
    }

    // no path found
    return solutionPath;
}


PathPlanner::PathPlanner(std::string mapfile)
{
    boost::filesystem::path path(mapfile);
    std::ifstream           file(path.string().c_str());
    std::string             line;

    if (!file)
    {
        std::cout << "Error: Could not open file " << mapfile << std::endl;
        return;
    }

    int numNodes = 0;
    // read first line of file to get number of nodes
    getline(file, line);
    numNodes = atoi(line.c_str());

    for (int i = 0; i < numNodes; i++)
    {
        getline(file, line);

        std::string       name;
        CostType          x;
        CostType          y;
        CostType          z;
        std::stringstream ss(line);
        ss >> name >> x >> y >> z;

        // add vertex to graph
        Vertex v = boost::add_vertex(m_graph);

        m_nodes.push_back(Vector3f(x, y, z));
        m_nameToIndex.insert(std::make_pair(name, i));

        m_posToName.insert(std::make_pair(v, name));  // only needed for the printRoute function
    }

    while (getline(file, line))
    {
        int from;
        int to;

        std::stringstream ss(line);
        ss >> from >> to;

        // add edge to graph
        // returns std::pair. first provides access to the line. second is a bool
        // variable that indicates whether the line was successfully added
        Edge     e     = boost::add_edge(from, to, m_graph).first;
        Vector3f r     = m_nodes[from] - m_nodes[to];
        m_weightmap[e] = sqrt(pow(r[0], 2) + pow(r[1], 2) + pow(r[2], 2));
    }
}

void PathPlanner::positionHelper(std::string s)
{
    // shift all positions that the start node will be at 0 0 0
    Vector3f start = m_nodes[m_nameToIndex[s]];
    for (auto& m_node : m_nodes)
    {
        m_node[0] -= start[0];
        m_node[1] -= start[1];
        m_node[2] -= start[2];
    }
}

void PathPlanner::printRoute(std::list<Vector<float>> solutionPath)
{
    // given the route, find the nodes that correspond to the route
    for (auto& solution : solutionPath)
    {
        // iterate over all nodes with an index
        for (int i = 0; i < m_nodes.size(); i++)
        {
            // check if the node is the same as the solution
            if (m_nodes[i][0] == solution[0] && m_nodes[i][1] == solution[1]
                && m_nodes[i][2] == solution[2])
            {
                std::cout << m_posToName[i] << std::endl;
            }
        }
    }
}

}
