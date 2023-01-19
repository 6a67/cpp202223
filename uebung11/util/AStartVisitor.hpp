#ifndef ASTARTVISITOR_HPP
#define ASTARTVISITOR_HPP

#include <boost/graph/astar_search.hpp>


namespace asteroids
{

    class GoalException : public std::exception
    {
    public:
        GoalException() : std::exception() {}
    };

    template<typename Vertex, typename Graph>
    class AStarVisitor : public boost::default_astar_visitor
    {
    public:
        AStarVisitor(Vertex goal) : m_goal(goal) {}

        void examine_vertex(Vertex u, const Graph& g)
        {
            if (u == m_goal)
            {
                throw GoalException();
            }
        }

    private:
        Vertex m_goal;


};

} // namespace asteroids


#endif //ASTARTVISITOR_HPP
