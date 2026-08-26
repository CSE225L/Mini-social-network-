#ifndef MEMBER3ALGORITHMS_H_INCLUDED
#define MEMBER3ALGORITHMS_H_INCLUDED

#include "Graph.h"

class Member3Algorithms
{
public:
    void BFS(int graph[][MAX_USERS], int n, int start);
    void friendSuggestions(int graph[][MAX_USERS], int n, int user);
    void mutualFriends(int graph[][MAX_USERS], int n, int user1, int user2);
    int degreesOfSeparation(int graph[][MAX_USERS], int n, int start, int target);
    void DFSIterative(int graph[][MAX_USERS], int n, int start);
    void DFSRecursive(int graph[][MAX_USERS], int n, int current, bool visited[]);
    void findCommunities(int graph[][MAX_USERS], int n);
};

#endif
