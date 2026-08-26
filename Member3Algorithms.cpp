#include <iostream>
#include "Member3Algorithms.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

void Member3Algorithms::BFS(int graph[][MAX_USERS], int n, int start)
{
    bool visited[MAX_USERS];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    Queue q;
    visited[start] = true;
    q.enqueue(start);

    cout << "BFS: ";

    while (!q.isEmpty())
    {
        int current = q.dequeue();
        cout << current << " ";

        for (int i = 0; i < n; i++)
        {
            if (graph[current][i] == 1 && visited[i] == false)
            {
                visited[i] = true;
                q.enqueue(i);
            }
        }
    }

    cout << endl;
}

void Member3Algorithms::friendSuggestions(int graph[][MAX_USERS], int n, int user)
{
    bool visited[MAX_USERS];
    int level[MAX_USERS];

    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        level[i] = -1;
    }

    Queue q;
    visited[user] = true;
    level[user] = 0;
    q.enqueue(user);

    cout << "Friend Suggestions: ";
    bool found = false;

    while (!q.isEmpty())
    {
        int current = q.dequeue();
        for (int i = 0; i < n; i++)
        {
            if (graph[current][i] == 1 && visited[i] == false)
            {
                visited[i] = true;
                level[i] = level[current] + 1;

                if (level[i] == 2)
                {
                    cout << i << " ";
                    found = true;
                }

                if (level[i] < 2)
                {
                    q.enqueue(i);
                }
            }
        }
    }

    if (!found)
    {
        cout << "None";
    }
    cout << endl;
}

void Member3Algorithms::mutualFriends(int graph[][MAX_USERS], int n, int user1, int user2)
{
    bool found = false;

    cout << "Mutual Friends: ";

    for (int i = 0; i < n; i++)
    {
        if (graph[user1][i] == 1 && graph[user2][i] == 1)
        {
            cout << i << " ";
            found = true;
        }
    }

    if (found == false)
    {
        cout << "None";
    }
    cout << endl;
}

int Member3Algorithms::degreesOfSeparation(int graph[][MAX_USERS], int n, int start, int target)
{
    bool visited[MAX_USERS];
    int distance[MAX_USERS];

    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        distance[i] = -1;
    }

    Queue q;
    visited[start] = true;
    distance[start] = 0;
    q.enqueue(start);

    while (!q.isEmpty())
    {
        int current = q.dequeue();

        if (current == target)
        {
            return distance[current];
        }

        for (int i = 0; i < n; i++)
        {
            if (graph[current][i] == 1 && visited[i] == false)
            {
                visited[i] = true;
                distance[i] = distance[current] + 1;
                q.enqueue(i);
            }
        }
    }

    return -1;
}

void Member3Algorithms::DFSIterative(int graph[][MAX_USERS], int n, int start)
{
    bool visited[MAX_USERS];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    Stack s;
    s.push(start);

    cout << "Iterative DFS: ";

    while (!s.isEmpty())
    {
        int current = s.pop();
        if (visited[current] == false)
        {
            visited[current] = true;
            cout << current << " ";

            for (int i = n - 1; i >= 0; i--)
            {
                if (graph[current][i] == 1 && visited[i] == false)
                {
                    s.push(i);
                }
            }
        }
    }

    cout << endl;
}

void Member3Algorithms::DFSRecursive(int graph[][MAX_USERS], int n, int current, bool visited[])
{
    visited[current] = true;
    cout << current << " ";

    for (int i = 0; i < n; i++)
    {
        if (graph[current][i] == 1 && visited[i] == false)
        {
            DFSRecursive(graph, n, i, visited);
        }
    }
}

void Member3Algorithms::findCommunities(int graph[][MAX_USERS], int n)
{
    bool visited[MAX_USERS];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    int community = 1;
    cout << "Communities:" << endl;

    for (int i = 0; i < n; i++)
    {
        if (visited[i] == false)
        {
            cout << "Community " << community << ": ";
            DFSRecursive(graph, n, i, visited);
            cout << endl;
            community++;
        }
    }
}
