#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <cstddef>

class Queue
{
private:
    struct QNode
    {
        int data;
        QNode* next;
    };

    QNode* front;
    QNode* rear;

public:
    Queue();
    ~Queue();
    void enqueue(int value);
    int dequeue();
    bool isEmpty();
};

#endif
