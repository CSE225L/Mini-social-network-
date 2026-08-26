#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    node<T>* temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template <class T>
void LinkedList<T>::Insert(T item)
{
    node<T>* n = new node<T>;

    n->data = item;
    n->next = head;
    head = n;
}

template <class T>
void LinkedList<T>::Print()
{
    node<T>* temp;

    temp = head;

    while(temp != NULL)
    {
        temp->data.Print();
        temp = temp->next;
    }
}

#include "User.h"

template class LinkedList<User>;
