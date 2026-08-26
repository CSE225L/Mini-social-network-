#ifndef GRAPH_H
#define GRAPH_H

#include "LinkedList.h"

template <class T>
class Graph
{
private:
    int size;
    T* users;
    LinkedList<T>* friends;

public:
    Graph(int);
    ~Graph();

    void AddUser(int, T);
    void AddFriend(int, int);
    void ShowFriends(int);
    T GetUser(int);
};

#endif
