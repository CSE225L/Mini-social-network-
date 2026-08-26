#include <iostream>
#include "Graph.h"
//#include "User.h"

using namespace std;

template <class T>
Graph<T>::Graph(int s)
{
    size = s;

    users = new T[size];
    friends = new LinkedList<T>[size];
}

template <class T>
Graph<T>::~Graph()
{
    delete[] users;
    delete[] friends;
}

template <class T>
void Graph<T>::AddUser(int index, T user)
{
    users[index] = user;
}

template <class T>
void Graph<T>::AddFriend(int first, int second)
{
    friends[first].Insert(users[second]);
    friends[second].Insert(users[first]);
}

template <class T>
void Graph<T>::ShowFriends(int index)
{
    cout << "Friends of " << users[index].getName() << ":" << endl;

    friends[index].Print();
}

template <class T>
T Graph<T>::GetUser(int index)
{
    return users[index];
}

template class Graph<User>;
