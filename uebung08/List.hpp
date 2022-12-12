/*
 * List.hpp
 *
 *  @date 02.12.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */


#ifndef LIST_H
#define LIST_H

namespace asteroids
{

/**
 * @brief   A simple generic list class
 */
template<typename T>
class List
{
public:
    /**
     * @brief Constructs an empty list.
     */
    List()
    : head(nullptr)
    {
    }

    /**
     * @brief  Destructor. Frees the generated nodes.
     */
    ~List();
    /**
     * @brief Inserts an item into the list, i.e. a new node
     *        constaining @ref item is created.
     * @param item To be inserted
     *
     */
    void insert(T item);

    /**
     * @brief Iterates over all items in the list and calls
     * the given function @ref do_something(...) for
     * every item stored in the list.
     *
     * @param do_something Function pointer to apply to all elements.
     */
    void for_each(void (*do_something)(T& item));

private:
    struct Node
    {
        Node* next;
        Node* prev;
        T     value;
    };

    Node* head;
};


}

#include "List.tcc"
#endif
/* end of include guard: LIST_H */
