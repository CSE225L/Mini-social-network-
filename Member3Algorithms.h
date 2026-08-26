#ifndef MEMBER3ALGORITHMS_H
#define MEMBER3ALGORITHMS_H

#include "Queue.h"
#include "Stack.h"

class Member3Algorithms

   {


public:


    void BFS(int graph[][100], int n, int start);               //BFS



    void friendSuggestions(int graph[][100], int n, int user);   //Friend Suggestions



    void mutualFriends(int graph[][100], int n, int user1, int user2);      //Mutual Friends



    int degreesOfSeparation(int graph[][100], int n, int start, int target);    //Degrees of Separation



    void DFSIterative(int graph[][100], int n, int start);                      //Iterative DFS



    void DFSRecursive(int graph[][100], int n, int current, bool visited[]);      //Recursive DFS



    void findCommunities(int graph[][100], int n);                          //Community Detection

             };

#endif
