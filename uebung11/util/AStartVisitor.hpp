#ifndef ASTARTVISITOR_HPP
#define ASTARTVISITOR_HPP

#include <boost/graph/astar_search.hpp>

namespace asteroids
{

// A custom exception class to be thrown when the goal vertex is found during the A* search
class GoalException : public std::exception
{
public:
    GoalException()
    : std::exception()
    {
    }
};

// A custom visitor class for the A* search that throws a GoalException when the goal vertex is
// found
template<typename Vertex, typename Graph>
class AStarVisitor : public boost::default_astar_visitor
{
public:
    // The constructor takes in the goal vertex
    AStarVisitor(Vertex goal)
    : m_goal(goal)
    {
    }

    // Overrides the examine_vertex function from the base class to throw the GoalException when the
    // goal vertex is found
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

}  // namespace asteroids


#endif  // ASTARTVISITOR_HPP
