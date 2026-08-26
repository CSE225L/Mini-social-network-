#include "Queue.h"

Queue::Queue()
{
    front=NULL;
    rear=NULL;
   }



Queue::~Queue()
   {
    while(!isEmpty())
    {
        dequeue();
    }
    }

void Queue::enqueue(int value)
{

    Node* newNode=new Node;

    newNode->data=value;
    newNode->next=NULL;

    if(rear==NULL)

      {
        front=newNode;
        rear=newNode;
    }

    else
    {

        rear->next=newNode;
        rear=newNode;
    }
    }

int Queue::dequeue()
   {
    if(isEmpty())
    {
        return-1;
    }

    Node* temp=front;
    int value=front->data;
    front=front->next;

    if (front==NULL)
    {

        rear=NULL;
    }

    delete temp;
    return value;
}

bool Queue::isEmpty()
   {

    return front==NULL;
    }
