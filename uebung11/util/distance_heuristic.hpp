#ifndef DISTANCE_HEURISTIC_HPP
#define DISTANCE_HEURISTIC_HPP

#include <boost/graph/astar_search.hpp>

namespace asteroids
{

    template<typename Graph, typename NodeMap>
    class distance_heuristic : public boost::astar_heuristic<Graph, float>
    {
    public:
//        typedef typename boost::property_traits<NodeMap>::value_type Location;
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;

        distance_heuristic(NodeMap l, Vertex goal)
                : m_location(l), m_goal(goal) {}

        float operator()(Vertex u)
        {
            auto goal = m_location[m_goal];
            auto current = m_location[u];
            float dx = goal[0] - current[0];
            float dy = goal[1] - current[1];
            float dz = goal[2] - current[2];
            return sqrt(dx * dx + dy * dy + dz * dz);
        }

        private:
        NodeMap m_location;
            Vertex m_goal;
    };



} // namespace asteroids



#endif //DISTANCE_HEURISTIC_HPP
