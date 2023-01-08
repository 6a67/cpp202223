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
private:
    class Node;

public:
    /**
     * @brief Constructs an empty list.
     */
    List<T>();
    /**
     * @brief  Destructor. Frees the generated nodes.
     */
    ~List<T>();
    /**
     * @brief Inserts an item into the list, i.e. a new node
     *        constaining @ref item is created.
     * @param item To be inserted
     *
     */
    void push_back(T item);

    /**
     * @brief Iterates over all items in the list and calls
     * the given function @ref do_something(...) for
     * every item stored in the list.
     *
     * @param do_something Function pointer to apply to all elements.
     */
    void for_each(void (*do_something)(T& item));

    class Iterator
    {
    public:
        /**
         * @brief   Constructs an iterator for the given list
         */
        Iterator(Node* node)
        : m_node(node)
        {
        }

        /**
         * @brief   Increments the iterator
         *
         * @return  A reference to the iterator
         */
        const Iterator& operator++()
        {
            m_node = m_node->next;
            return *this;
        }

        /**
         * @brief   Checks if two iterators are not equal
         *
         * @param   other The other iterator
         * @return  True if the iterators are not equal, false otherwise
         */
        bool operator!=(const Iterator& other) const { return m_node != other.m_node; }

        /**
         * @brief   Returns the item stored in the current node
         *
         * @return  The item stored in the current node
         */
        T& operator*() const { return m_node->data; }

    private:
        Node* m_node;
    };

    /**
     * @brief Returns an iterator to the first element of the list.
     */
    Iterator begin() { return Iterator(m_root); }

    /**
     * @brief Returns an iterator to the pointer behind the last element of the list.
     */
    Iterator end() { return Iterator(nullptr); }


private:
    /**
     * @brief Struct to represent an inner node of the list.
     */
    class Node
    {
    public:
        Node(T _data, Node* _next)
        : data(_data)
        , next(_next){};
        friend class List::Iterator;
        friend class List;

    private:
        T     data;
        Node* next;
    };

    // List* m_root;
    Node* m_root;
};

}

#include "List.tcc"
#endif
/* end of include guard: LIST_H */
