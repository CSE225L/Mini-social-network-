#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include "User.h"
#include <cstddef>

template <class T>
struct Node
{
    T data;
    Node<T>* next;
};

template <class T>
class LinkedList
{
private:
    Node<T>* head;

public:
    LinkedList()
    {
        head = NULL;
    }

    ~LinkedList()
    {
        Node<T>* temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void Insert(T item)
    {
        Node<T>* n = new Node<T>;
        n->data = item;
        n->next = head;
        head = n;
    }

    bool Contains(T item)
    {
        Node<T>* temp = head;
        while (temp != NULL)
        {
            if (temp->data == item)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void Delete(T item)
    {
        Node<T>* temp = head;
        Node<T>* prev = NULL;

        while (temp != NULL && !(temp->data == item))
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            return;
        }

        if (prev == NULL)
        {
            head = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }
        delete temp;
    }

    void Print()
    {
        Node<T>* temp = head;
        if (temp == NULL)
        {
            cout << "(none)" << endl;
            return;
        }
        while (temp != NULL)
        {
            temp->data.Print();
            temp = temp->next;
        }
    }

    int Length()
    {
        int count = 0;
        Node<T>* temp = head;
        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void CopyTo(T arr[], int& n)
    {
        n = 0;
        Node<T>* temp = head;
        while (temp != NULL)
        {
            arr[n] = temp->data;
            n++;
            temp = temp->next;
        }
    }
};

#endif
