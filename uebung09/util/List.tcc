/*
 * List.tcc
 *
 *  @date 02.12.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include <iostream>

namespace asteroids
{

template<typename T> List<T>::List()
{
   m_root = nullptr;
}

template<typename T> List<T>::~List()
{
   Node* next = m_root;
   do
   {
      Node* to_delete = next;
      next = next->next;
      delete to_delete;
   } 
   while(next);
}

template<typename T> void List<T>::push_back(T item)
{
   if (m_root == nullptr) 
   {
      m_root = new Node(item, nullptr);
   } 
   else
   {
      m_root = new Node(item, m_root);
   }
}

template<typename T> void List<T>::for_each(void (*do_something)(T& item))
{
   Node* tmp = m_root;
   while (tmp != nullptr) 
   {
      do_something(tmp->data);
      tmp = tmp->next;
   }
}

} // namespace asteroids
