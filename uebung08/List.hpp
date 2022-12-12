#ifndef LIST_HPP
#define LIST_HPP

namespace asteroids
{
template<typename T>
class List
{
private:
    struct Node
    {
        Node* next;
        Node* prev;
        T     value;
    };

    Node* head;

public:
    List()
    : head(nullptr)
    {
    }

    void insert(T item);
    void for_each(void (*do_something)(T& item));

    ~List();
};
}  // namespace asteroids

#include "List.tcc"
#endif