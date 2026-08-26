#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
private:
      struct Node
    {
    int data;
    Node* next;
    };


    Node*front;
    Node*rear;

public:
    Queue();
    ~Queue();


    void enqueue(int value);
    int dequeue();
    bool isEmpty();
};

#endif
