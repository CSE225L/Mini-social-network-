#include "InboxQueue.h"

InboxQueue::InboxQueue()
{
    front = 0;
    rear = -1;
    length = 0;
}

bool InboxQueue::isEmpty() const
{
    return length == 0;
}

bool InboxQueue::isFull() const
{
    return length == MAX_INBOX;
}

void InboxQueue::enqueue(Notification item)
{
    if (isFull())
    {
        cout << "Inbox is full." << endl;
        return;
    }
    rear = (rear + 1) % MAX_INBOX;
    data[rear] = item;
    length++;
}

Notification InboxQueue::dequeue()
{
    Notification empty;
    empty.fromID = 0;
    empty.toID = 0;
    empty.type = 0;
    empty.text = "";

    if (isEmpty())
    {
        return empty;
    }

    Notification item = data[front];
    front = (front + 1) % MAX_INBOX;
    length--;
    return item;
}

void InboxQueue::displayForUser(int userID)
{
    if (isEmpty())
    {
        cout << "Inbox is empty." << endl;
        return;
    }

    cout << endl << "Pending Requests & Notifications:" << endl;
    bool found = false;
    int index = front;
    for (int i = 0; i < length; i++)
    {
        if (data[index].toID == userID)
        {
            found = true;
            if (data[index].type == 1)
            {
                cout << "[REQUEST] From user " << data[index].fromID
                     << " to user " << data[index].toID << " | "
                     << data[index].text << endl;
            }
            else
            {
                cout << "[NOTICE] " << data[index].text << endl;
            }
        }
        index = (index + 1) % MAX_INBOX;
    }

    if (!found)
    {
        cout << "No items for this user." << endl;
    }
}

bool InboxQueue::hasPendingRequest(int fromID, int toID)
{
    int index = front;
    for (int i = 0; i < length; i++)
    {
        if (data[index].type == 1 && data[index].fromID == fromID && data[index].toID == toID)
        {
            return true;
        }
        index = (index + 1) % MAX_INBOX;
    }
    return false;
}

bool InboxQueue::removeRequest(int fromID, int toID)
{
    if (isEmpty())
    {
        return false;
    }

    Notification temp[MAX_INBOX];
    int tempLen = 0;
    bool removed = false;
    int index = front;

    for (int i = 0; i < length; i++)
    {
        bool match = (data[index].type == 1 && data[index].fromID == fromID && data[index].toID == toID);
        if (match && !removed)
        {
            removed = true;
        }
        else
        {
            temp[tempLen] = data[index];
            tempLen++;
        }
        index = (index + 1) % MAX_INBOX;
    }

    front = 0;
    rear = -1;
    length = 0;
    for (int i = 0; i < tempLen; i++)
    {
        enqueue(temp[i]);
    }
    return removed;
}
