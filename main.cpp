#include <iostream>

#include "User.h"
#include "Graph.h"
#include "SortedList.h"
#include "UnsortedList.h"

using namespace std;

int main()
{
    int n;

    cout << "Enter number of users: ";
    cin >> n;

    Graph<User> graph(n);


    // Add users
    for(int i = 0; i < n; i++)
    {
        int id;
        string name;

        cout << "Enter ID: ";
        cin >> id;

        cout << "Enter Name: ";
        cin >> name;

        User user(id, name);

        graph.AddUser(i, user);
    }


    // Add friendship
    int first, second;

    cout << "Enter two user indexes to make friends: ";
    cin >> first >> second;

    graph.AddFriend(first, second);

    cout << endl;

    graph.ShowFriends(first);


    // Sorted Friend List
    SortedList friendList;

    friendList.Insert(graph.GetUser(first));
    friendList.Insert(graph.GetUser(second));

    cout << endl;
    cout << "Alphabetical Friend List:" << endl;

    friendList.Print();


    // Blocked User List
    UnsortedList blockedList;

    int block;

    cout << endl;
    cout << "Enter blocked user index: ";
    cin >> block;

    blockedList.Insert(graph.GetUser(block));

    cout << "Blocked Users:" << endl;

    blockedList.Print();

    return 0;
}
