#ifndef LIST_TCC
#define LIST_TCC
namespace asteroids
{

template<typename T>
void List<T>::insert(T item)
{
    // insert item to the end of the list
    Node* new_node  = new Node;
    new_node->value = item;
    new_node->next  = nullptr;

    // if the list is empty, set the head to the new node
    if (head == nullptr)
    {
        head = new_node;
    }
    else  // otherwise iterate to the end
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next  = new_node;
    }
}

template<typename T>
void List<T>::for_each(void (*do_something)(T item))
{
    Node* current = head;
    while (current != nullptr)
    {
        do_something(current->value);
        current = current->next;
    }
}

template<typename T>
List<T>::~List()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

}  // namespace asteroids
#endif