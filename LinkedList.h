#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
struct node
{
    T data;
    node<T>* next;
};

template <class T>
class LinkedList
{
private:
    node<T>* head;

public:
    LinkedList();
    ~LinkedList();

    void Insert(T);
    void Print();
};

#endif
