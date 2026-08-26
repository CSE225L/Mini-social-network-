#ifndef INBOXQUEUE_H_INCLUDED
#define INBOXQUEUE_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

const int MAX_INBOX = 100;

struct Notification
{
    int fromID;
    int toID;
    int type;
    string text;
};

class InboxQueue
{
private:
    Notification data[MAX_INBOX];
    int front;
    int rear;
    int length;

public:
    InboxQueue();
    bool isEmpty() const;
    bool isFull() const;
    void enqueue(Notification item);
    Notification dequeue();
    void displayForUser(int userID);
    bool removeRequest(int fromID, int toID);
    bool hasPendingRequest(int fromID, int toID);
};

#endif
