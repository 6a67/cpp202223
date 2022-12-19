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
template<typename T> class List
{
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

private:

      /**
       * @brief Struct to represent an inner node of the list.
       */
      class Node {
      public:
            Node( T _data, Node* _next) : data(_data), next(_next) {};
	  //friend class List::Iterator;
            friend class List;
      private:
         T data;
         Node* next;
      };

      List* m_root;

};

}

#include "List.tcc"
#endif
/* end of include guard: LIST_H */
