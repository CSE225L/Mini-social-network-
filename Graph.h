#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "LinkedList.h"
#include <iostream>
using namespace std;

const int MAX_USERS = 100;

template <class T>
class Graph
{
private:
    int capacity;
    int userCount;
    T* users;
    LinkedList<T>* friends;

public:
    Graph(int s)
    {
        capacity = s;
        userCount = 0;
        users = new T[capacity];
        friends = new LinkedList<T>[capacity];
    }

    ~Graph()
    {
        delete[] users;
        delete[] friends;
    }

    int GetUserCount() const
    {
        return userCount;
    }

    int FindIndexByID(int id)
    {
        for (int i = 0; i < userCount; i++)
        {
            if (users[i].getID() == id)
            {
                return i;
            }
        }
        return -1;
    }

    void AddUser(T user)
    {
        if (userCount >= capacity)
        {
            return;
        }
        users[userCount] = user;
        userCount++;
    }

    void AddUser(int index, T user)
    {
        if (index < 0 || index >= capacity)
        {
            return;
        }
        users[index] = user;
        if (index + 1 > userCount)
        {
            userCount = index + 1;
        }
    }

    void AddFriend(int first, int second)
    {
        if (first < 0 || second < 0 || first >= userCount || second >= userCount)
        {
            return;
        }
        if (first == second)
        {
            return;
        }
        if (!friends[first].Contains(users[second]))
        {
            friends[first].Insert(users[second]);
        }
        if (!friends[second].Contains(users[first]))
        {
            friends[second].Insert(users[first]);
        }
    }

    void RemoveFriend(int first, int second)
    {
        if (first < 0 || second < 0 || first >= userCount || second >= userCount)
        {
            return;
        }
        friends[first].Delete(users[second]);
        friends[second].Delete(users[first]);
    }

    bool AreFriends(int first, int second)
    {
        if (first < 0 || second < 0 || first >= userCount || second >= userCount)
        {
            return false;
        }
        return friends[first].Contains(users[second]);
    }

    void ShowFriends(int index)
    {
        if (index < 0 || index >= userCount)
        {
            cout << "Invalid user." << endl;
            return;
        }
        cout << "Friends of " << users[index].getName() << ":" << endl;
        friends[index].Print();
    }

    T GetUser(int index)
    {
        return users[index];
    }

    void FillFriendIDs(int index, int ids[], int& n)
    {
        T arr[MAX_USERS];
        n = 0;
        friends[index].CopyTo(arr, n);
        for (int i = 0; i < n; i++)
        {
            ids[i] = arr[i].getID();
        }
    }

    void BuildAdjMatrix(int matrix[][MAX_USERS])
    {
        for (int i = 0; i < userCount; i++)
        {
            for (int j = 0; j < userCount; j++)
            {
                matrix[i][j] = 0;
            }
        }
        for (int i = 0; i < userCount; i++)
        {
            T arr[MAX_USERS];
            int n = 0;
            friends[i].CopyTo(arr, n);
            for (int k = 0; k < n; k++)
            {
                int j = FindIndexByID(arr[k].getID());
                if (j != -1)
                {
                    matrix[i][j] = 1;
                }
            }
        }
    }
};

#endif
