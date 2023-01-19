#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>
#include <sstream>
#include <boost/graph/astar_search.hpp>
#include "AStartVisitor.hpp"
#include "distance_heuristic.hpp"


#include "PathPlanner.hpp"

namespace asteroids
{




std::list<Vector<float> > PathPlanner::getPath(Vector<float> position, std::string s, std::string e)
{
    // TODO: Plan a path from s to e using the A* implementaion
    // of the Boost Graph Library. Add the positions of the 
    // visited nodes of the solution to this list.
    std::list<Vector<float> > solutionPath;
    positionHelper(s);
//    std::tuple<std::string, float, float, float> startNode;
//    std::tuple<std::string, float, float, float> endNode;

    // TODO: even needed?
    // find s and e as name in m_nodes
//    for (auto & m_node : m_nodes) {
//        if (std::get<0>(m_node) == s) {
//            startNode = m_node;
//        } else if (std::get<0>(m_node) == e) {
//            endNode = m_node;
//        }
//    }

    // get vertex from name
    int start = m_nameToIndex[s];
    int end = m_nameToIndex[e];

    std::vector<Vertex> path(num_vertices(m_graph));
    std::vector<float> dist(num_vertices(m_graph));

    try
    {
        boost::astar_search(
            m_graph,
            start,
            distance_heuristic<Graph, std::vector<Vector3f>>(m_nodes, end),
            boost::predecessor_map(&path[0]).distance_map(&dist[0]).
            visitor(AStarVisitor<Vertex, Graph>(end))
        );
    }
    catch (GoalException goalException)
    {
        // found a path to the goal
        for (Vertex v = end;; v = path[v])
        {
//            Vector3f pos;
//            pos[0] = m_nodes[v][0];
//            pos[1] = m_nodes[v][1];
//            pos[2] = m_nodes[v][2];
            solutionPath.push_front(m_nodes[v]);
            if (path[v] == v)
            {
                break;
            }
        }
        printRoute(solutionPath);
        return solutionPath;
    }

    std::cout << "No path found!" << std::endl;
    solutionPath.push_back(position);
    return solutionPath;
}


PathPlanner::PathPlanner (std::string mapfile) 
{
    // TODO: Parse file and build graph representation as
    // for planning with BGL.

    boost::filesystem::path path(mapfile);
    std::ifstream file(path.string().c_str());
    std::string line;

    if(!file) {
        std::cout << "Error: Could not open file " << mapfile << std::endl;
        return;
    }

    int numNodes = 0;
    // read first line of file to get number of nodes
    getline(file, line);
    numNodes = atoi(line.c_str());

    for(int i = 0; i < numNodes; i++) {
        getline(file, line);

        std::string name;
        float x;
        float y;
        float z;
        std::stringstream ss(line);
        ss >> name >> x >> y >> z;
//        m_nodes.push_back(std::make_tuple(name, x, y, z)); // TODO: even needed?
//        m_nodeMap.insert(std::make_pair(name, std::make_tuple(x, y, z)));

//        std::cout << "Node: " << name << " " << x << " " << y << " " << z << std::endl;

        // add vertex to graph
        auto v = boost::add_vertex(m_graph);
//        m_planet_names[v] = name; // TODO: even needed?
        m_posToName.insert(std::make_pair(v, name)); // TODO: even needed?

        // add name to map
        m_nameToPos.insert(std::make_pair(name, v));

        m_nodes.push_back(Vector3f(x, y, z));
        m_nameToIndex.insert(std::make_pair(name, i));
    }

    while(getline(file, line)) {
        int from;
        int to;

        std::stringstream ss(line);
        ss >> from >> to;
//        m_edges.push_back(std::make_tuple(from, to));

        // add edge to graph
        auto e = boost::add_edge(from, to, m_graph).first; // returns std::pair. first provides access to the line. second is a bool variable that indicates whether the line was successfully added
//        m_weightmap[e] = sqrt(pow(get<1>(m_nodes[from]) - get<1>(m_nodes[to]), 2) + pow(get<2>(m_nodes[from]) - get<2>(m_nodes[to]), 2) + pow(get<3>(m_nodes[from]) - get<3>(m_nodes[to]), 2));
        m_weightmap[e] = sqrt(pow(m_nodes[from][0] - m_nodes[to][0], 2) + pow(m_nodes[from][1] - m_nodes[to][1], 2) + pow(m_nodes[from][2] - m_nodes[to][2], 2));

    }
}

void PathPlanner::positionHelper(std::string s)
{
    // Shift all positions that the start node will be at 0 0 0
    Vector3f start = m_nodes[m_nameToIndex[s]];
    for (auto & m_node : m_nodes) {
        m_node[0] -= start[0];
        m_node[1] -= start[1];
        m_node[2] -= start[2];
    }
}

void PathPlanner::printRoute(std::list<Vector<float>> solutionPath) {
    // given the route, find the nodes that correspond to the route
    for (auto & solution : solutionPath) {
        // iterate over all nodes with an index
        for(int i = 0; i < m_nodes.size(); i++) {
            // check if the node is the same as the solution
            if (m_nodes[i][0] == solution[0] && m_nodes[i][1] == solution[1] && m_nodes[i][2] == solution[2]) {
                std::cout << m_posToName[i] << std::endl;
            }
        }
    }
}

}
