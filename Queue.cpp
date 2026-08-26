#include "Queue.h"
#include <cstddef>

Queue::Queue()
{
    front = NULL;
    rear = NULL;
}

Queue::~Queue()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

void Queue::enqueue(int value)
{
    QNode* newNode = new QNode;
    newNode->data = value;
    newNode->next = NULL;

    if (rear == NULL)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

int Queue::dequeue()
{
    if (isEmpty())
    {
        return -1;
    }

    QNode* temp = front;
    int value = front->data;
    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    delete temp;
    return value;
}

bool Queue::isEmpty()
{
    return front == NULL;
}
